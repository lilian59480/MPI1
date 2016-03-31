#ifndef H_MAIN
#define H_MAIN

#include "common.h"

#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

void lireParamShell (int argc, char** argv);
short hoverMenu(TTF_Font* Font,char* String,int TTFW, int TTFH,SDL_Event event,SDL_Rect Rect) ;
short clickMenu(TTF_Font* Font,char* String,int TTFW, int TTFH,SDL_Event event,SDL_Rect Rect) ;

#endif