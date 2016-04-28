#ifndef H_MAIN
#define H_MAIN

#include "common.h"
#include "best.h"
#include "menu.h"

void lireParamShell (int argc, char** argv);
short hoverMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
short clickMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
SDL_Rect rangMenu (SDL_Surface* Surface, short rang);

#endif