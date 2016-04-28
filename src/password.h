#ifndef H_PASS
#define H_PASS

#include "common.h"


#define LARGEUR_FENETREPASS 400
#define HAUTEUR_FENETREPASS 300
#define PASSMAX 10

int password();
short hoverPass (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
short clickPass (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;

#endif