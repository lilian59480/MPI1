#ifndef H_JEU
#define H_JEU

#include "common.h"
#include <time.h>

#define TAILLEPLATEAUMAX 10

typedef int T_Case;

typedef struct {
    T_Case plateau[TAILLEPLATEAUMAX][TAILLEPLATEAUMAX];
    int taillexy;
} T_Cases;

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte);
void melangercase (T_Cases* plateau);
void _debugT_Cases(T_Cases* plateau);

#endif