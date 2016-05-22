#ifndef H_MENU
#define H_MENU

#define NBRNIVEAU 20

#include "common.h"
#include "jeu.h"

void fenetreChoixNiveau (SDL_Window* fenetre, T_MScore* score, Mix_Chunk* gSound,Mix_Music* gMusic, short* musique, short* onoff);

#endif