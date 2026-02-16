#ifndef __PARSER_H__
#define __PARSER_H__ 1

struct Resultat {
	char * nom;
	char * prenoms;
	char * resultat;
	int homonyme;
};
typedef struct Resultat * tResultat;

extern tResultat * parse(char *, int *);
extern void destroy_resultat(tResultat *);
extern void display_resultat(tResultat);

extern int stringeq(char *, char *);
extern void destroy_array(tResultat **, int);


extern void parse_command(char *, int size, char ** cmd, char ** next);
extern char * find_argument(char * input, char * name);

#endif
