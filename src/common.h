#ifndef H_COMMON
#define H_COMMON

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define IMGICONE "./img/icone.png"
#define ERASERFONT "./font/Eraser.ttf"
#define SCOREFILEBINARY "./score"
#define IMAGEJEUDIRECTORY "./img/puzzle/"
#define IMAGEJEUSECRETDIRECTORY "./img/puzzle/.secret/"

#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

#define METHODE_RAPIDE 0
#define METHODE_BELLE 1

typedef char T_Nom[20];
typedef unsigned int T_Score;

typedef struct
{
    T_Nom Nom;
    T_Score Score;
}  T_Entree;

typedef T_Entree T_Tableau[5];

typedef struct
{
    T_Tableau Scores;
} T_MScore;

SDL_Window* creerFenetre (SDL_Window* fenetre, char* titre);
SDL_Surface* chargerImage (SDL_Surface* image, char* chemin);
TTF_Font* chargerPolice (TTF_Font* font, char* chemin, int taille);
void libererPolice (TTF_Font* font);
SDL_Surface* creerTexte (SDL_Surface* surface, short methode, TTF_Font* font, char* texte, SDL_Color couleur);
short hoverMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
short clickMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
SDL_Rect rangMenu (SDL_Surface* Surface, short rang);


#endif
