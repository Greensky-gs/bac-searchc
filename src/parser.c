#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_SIZE 10
#define MAX_VAL_SIZE 1024

static char * find_key(FILE * file, int * psize) {
	int guils = 0;
	char c;
	int size = 0;

	char * key = calloc(15, sizeof(char));

	while (guils < 2) {
		c = getc(file);
		if (guils == 1 && c != '"') key[size++] = c;

		if (c == '"') guils++;
	}

	*psize = size;
	return key;
}
static char * parse_text(FILE * file, int * psize) {
	char temp[MAX_VAL_SIZE] = {0};

	int i = 0;
	int guils = 0;
	while (guils < 2) {
		char c = getc(file);

		if (guils == 1 && c != '"') temp[i++] = c;
		if (c == '"') guils++;
	}

	char * text;
   	if ((text = calloc(i + 1, sizeof(char))) == NULL) return NULL;
	*psize = i;
	i = 0;
	while (i < *psize) {
		text[i] = temp[i];
		i++;
	}

	return text;
}

int stringeq(char * a, char *b) {
	int i = 0;
	while (a[i] != 0 && b[i] != 0) {
		if (a[i] != b[i]) return 0;
		i++;
	}

	if (a[i] != b[i]) return 0;
	return 1;
}
static int parse_bool(FILE * file) {
	char boolean[8] = {0};
	int i = 0;
	char c;

	while ((c = getc(file)) != ',') {
		if (c == '}') break;
		if (c != ':') boolean[i++] = c;
	}

	return stringeq(boolean, "true");
}
static tResultat parse_one(FILE * file) {
	if (getc(file) != '{') return NULL;
	
	tResultat resultat;
	if ((resultat = malloc(sizeof(struct Resultat))) == NULL) return NULL;

	int i = 0;

	while (i < 4) {
		int size;
		char * key = find_key(file, &size);

		if (stringeq(key, "nom")) {
			int textsize;
			char * val = parse_text(file, &textsize);

			resultat->nom = val;
		}
		if (stringeq(key, "prenoms")) {
			int textSize;
			char * val = parse_text(file, &textSize);

			resultat->prenoms = val;
		}
		if (stringeq(key, "resultat")) {
			int textSize;
			char * val = parse_text(file, &textSize);

			resultat->resultat = val;
		}
		if (stringeq(key, "homonyme")) {
			int boolean = parse_bool(file);

			resultat->homonyme = boolean;
		}

		i++;
		free(key);
	}

	return resultat;
}
static int count_entries(FILE * file) {
	int count = 0;
	int i = 0;
	int read;

	while ((read = getc(file)) != EOF) {
		if ((char)read == '}') count++;
	}

	fseek(file, 0, SEEK_SET);

	return count;
}

void destroy_resultat(tResultat * p) {
	free((*p)->nom);
	free((*p)->prenoms);
	free((*p)->resultat);
	free(*p);
}
void display_resultat(tResultat res) {
	printf("\x1b[94m%s \x1b[32m%s\x1b[0m : %s\n", res->prenoms, res->nom, res->resultat);
}

tResultat * parse(char * file_name, int * psize) {
	FILE * file;
	if ((file = fopen(file_name, "rt")) == NULL) return NULL;

	int entries = count_entries(file);
	tResultat * array;
	if ((array = malloc(sizeof(tResultat) * entries)) == NULL) return NULL;

	getc(file);

	int i = 0;
	tResultat res;
	while ((res = parse_one(file)) != NULL) {
		array[i++] = res;
		getc(file);
	}
	*psize = entries;

	fclose(file);
	return array;
}

void destroy_array(tResultat ** parr, int size) {
	int i = 0;
	while (i++ < size) {
		destroy_resultat(&(*parr)[i - 1]);
	}

	free(*parr);
	*parr = 0;
}

static int compare_from(char * input, char * motif, int start, int * psize) {
	int i = start;
	while (input[i] != 0 && motif[i - start] != 0) {
		if (input[i] != motif[i - start]) return 0;
		i++;
	}

	if (input[i] == 0) return 0;
	if (motif[i - start] != 0) return 0;


	*psize = i - start;
	return input[i] == ' ';
}

char * find_argument(char * input, char * name) {
	int i = 0;
	while (input[i] != 0) {
		int size;
		if (compare_from(input, name, i, &size) == 1) {
			int j = i + size + 1;

			char * arg;
			if ((arg = malloc(1024 * sizeof(char))) == NULL) {
				printf("An error occured\n");
				return NULL;
			}

			int start = j;
			while (input[j] != 0 && input[j] != ' ' && j < 1023) {
				arg[j - start] = input[j];
				j++;	
			}
			arg[j - start] = 0;
			return arg;
		}
		i++;
	}
}
void parse_command(char * input, int size, char ** name, char ** next) {
	int i = 0;

	while (input[i++] != ' ' && input[i] != 0) {};

	if ((*name = calloc(i + 1, sizeof(char))) == NULL) {
		*name = NULL;
		*next = NULL;
		return;
	}

	if ((*next = calloc(size - i + 1, sizeof(char))) == NULL) {
		free(*name);
		return;
	}

	if (input[i] == 0) {
		int j = 0;
		while(j++ < i) {
			(*name)[j - 1] = input[j - 1];
		}

		return;
	}

	int j = 0;
	while (j++ < i - 1) {
		(*name)[j - 1] = input[j - 1];
	}
	int start = j;
	while (j < size) {
		(*next)[j - start] = input[j];
		j++;
	}
}
