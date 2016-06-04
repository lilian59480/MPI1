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

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte, short r, short v, short b, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff , unsigned long scoreactuel, short mdp);
void melangercase (T_Cases* plateau);
void _debugT_Cases (T_Cases* plateau);
short validerCase (T_Cases* plateau);
void verifierCouleur (short* r, short* v, short* b);
void drawEmptyRect (SDL_Surface* surf, int posX, int posY, int width);
void drawGrille (SDL_Surface* surface, int posX, int posY, int taillecase, int nbcase);

void setPixel(SDL_Surface* surf,int x, int y, Uint32 coul);
void setPixelVerif(SDL_Surface* surf,int x, int y, Uint32 coul);
void echangerEntiers(int* x, int* y);
void ligne(SDL_Surface* surf, int x1, int y1, int x2, int y2, Uint32 coul);
void ligneHorizontale(SDL_Surface* surf,int x, int y, int w, Uint32 coul);
void ligneVerticale(SDL_Surface* surf,int x, int y, int h, Uint32 coul);
void disque(SDL_Surface* surf, int cx, int cy, int rayon, int coul);
void heart(SDL_Surface* surface, short x, short y);
void coeurcoeur(SDL_Surface* surface);

void wine(T_MScore* score, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff, unsigned long scorefinal);
void loose(Mix_Chunk* gSound);
Uint32 supprimerpoints(Uint32 intervalle, void *param) ;

#endif