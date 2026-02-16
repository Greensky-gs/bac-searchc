#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "tools.h"

#define LINE_MAX_SIZE 4096

int strsize(char * input) {
	int i = 0;
	while (input[i++] != 0) {};
	return i - 1;
}
void trim(char * input) {
	int i = 0;
	while (input[i] != 0) {
		if (input[i] == '\n') {
			input[i] = 0;
			break;
		}
		i++;
	}
}

int main() {
	char * name = "/home/green/Documents/github/bac-scrap/data/copy.json";
	int count = 0;

	char * line;
	if ((line = malloc(sizeof(char) * LINE_MAX_SIZE)) == NULL) {
		printf("Cannot allocate line buffer\n");
		return 3;
	}

	tResultat * array;
	if ((array = parse(name, &count)) == NULL) {
		printf("Error while parsing\n");
		return 1;
	}
	if (count == 0) {
		printf("No entry found\n");
		return 2;
	}

	line[4095] = 0;
	while (1) {
		printf("> \x1b[94m");
		fflush(stdout);

		fgets(line, LINE_MAX_SIZE, stdin);
		trim(line);

		printf("\x1b[0m");
		int size = strsize(line);
		if (size == 0) continue;

		char * cmd, * next;
		parse_command(line, size, &cmd, &next);

		if (cmd == NULL) {
			printf("No command\n");
			if (next != NULL) free(next);
			continue;
		}
		if (stringeq(cmd, "exit")) {
			printf("Bye ;)\n");
			if (next != NULL) free(next);
			free(cmd);
			destroy_array(&array, count);
			free(line);
			return 0;
		}
		if (next == NULL) {
			printf("No args\n");
			continue;
		}

		if (stringeq(cmd, "search")) {
			char * name = find_argument(next, "--name");
			char * prenom = find_argument(next, "--prenom");
			
			if (name == NULL && prenom == NULL) {
				printf("\x1b[91mEmpty search\x1b[0m\n");
			}
			if (name != NULL) lowercase(name, NULL);
			if (prenom != NULL) lowercase(prenom, NULL);

			int c = 0;
			int matches = 0;
			while (c != count) {
				tResultat res = array[c];

				if (is_matching(res, name, prenom)) {
					matches++;
					display_resultat(res);
				}

				c++;
			}

			printf("Found \x1b[92m%d\x1b[0m\n", matches);
			
			if (name != NULL) free(name);
			if (prenom != NULL) free(prenom);
		} else if (stringeq(cmd, "clear")) {
			printf("\e[1;1H\e[2J");
		} else {
			printf("\x1b[31mUnknown command\x1b[0m\n");
		}

	
		free(next);
		free(cmd);
	}

	destroy_array(&array, count);
	free(line);
	return 0;
}
