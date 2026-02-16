#include <string.h>
#include "tools.h"
#include "parser.h"
#include <stdio.h>

int resultat_prenom_includes(tResultat res, char * a) {
	char buffer[1024];
	lowercase(res->prenoms, buffer);
	return strstr(buffer, a) != NULL;
}

int resultat_name_includes(tResultat res, char * a) {
	char buffer[1024];
	lowercase(res->nom, buffer);
	return strstr(buffer, a) != NULL;
}

int is_matching(tResultat res, char * name, char * prenom) {
	if (name != NULL && !resultat_name_includes(res, name)) return 0;
	if (prenom != NULL && !resultat_prenom_includes(res, prenom)) return 0;
	return 1;
}

void lowercase(char * input, char * cpy) {
	int i = 0;
	while (input[i] != 0) {
		if (input[i] >= 65 && input[i] <= 90) {
			if (cpy == NULL) {
				input[i] += 32;
			} else {
				cpy[i] = input[i] + 32;
			}
		} else if (cpy != NULL) {
			cpy[i] = input[i];
		}
		i++;
	}
	if (cpy != NULL) cpy[i] = 0; 
}
