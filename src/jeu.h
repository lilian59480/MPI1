#ifndef H_JEU
#define H_JEU

#include "common.h"
#include <time.h>

#define TAILLEPLATEAUMAX 10

typedef int T_Case;

typedef struct
{
    T_Case plateau[TAILLEPLATEAUMAX][TAILLEPLATEAUMAX];
    int taillexy;
    T_Case selectionne;
} T_Cases;

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte, short r, short v, short b );
void melangercase (T_Cases* plateau);
void _debugT_Cases (T_Cases* plateau);
short validerCase (T_Cases* plateau);
void verifierCouleur (short* r, short* v, short* b);
void drawEmptyRect (SDL_Surface* surf, int posX, int posY, int width);
void drawGrille (SDL_Surface* surface, int posX, int posY, int taillecase, int nbcase);

#endif