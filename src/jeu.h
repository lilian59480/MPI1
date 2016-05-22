#ifndef H_JEU
#define H_JEU

#include "common.h"
#include <time.h>

#define TAILLEPLATEAUMAX 10
#define PSEUDOMAX 16

typedef int T_Case;

typedef struct
{
    T_Case plateau[TAILLEPLATEAUMAX][TAILLEPLATEAUMAX];
    int taillexy;
    T_Case selectionne;
} T_Cases;

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte, short r, short v, short b, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff );
void melangercase (T_Cases* plateau);
void _debugT_Cases (T_Cases* plateau);
short validerCase (T_Cases* plateau);
void verifierCouleur (short* r, short* v, short* b);
void drawEmptyRect (SDL_Surface* surf, int posX, int posY, int width);
void drawGrille (SDL_Surface* surface, int posX, int posY, int taillecase, int nbcase);
void wine(T_MScore* score, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff);
void loose(Mix_Chunk* gSound);

#endif