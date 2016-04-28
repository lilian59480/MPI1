#ifndef H_BEST
#define H_BEST

#include "common.h"

#define PLACEGAUCHE 0
#define PLACEDROITE 1

void fenetreMScore (SDL_Window* fenetre, T_MScore* score);
short ecrireMeilleurScore (T_MScore* scores);
short lireMeilleurScore (T_MScore* scores);
void resetScores (T_MScore* score);
SDL_Rect rangScores (SDL_Surface* Surface, short rang, short place);
#endif