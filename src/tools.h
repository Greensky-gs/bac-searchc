#ifndef __TOOLS_H__
#define __TOOLS_H__ 1

#include "parser.h"

extern int resultat_name_includes(tResultat, char *);
extern int resultat_prenom_includes(tResultat, char *);

extern int is_matching(tResultat, char *, char *);
extern void lowercase(char *, char *);

#endif
