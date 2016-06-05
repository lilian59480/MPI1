#ifndef H_COMMON
#define H_COMMON

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define TITREJEU "Arcade 2i"

#define IMGICONE "./img/icone.png"

#define ERASERFONT "./font/Eraser.ttf"
#define HELVFONT "./font/helv.ttf"
#define CONTFUFONT "./font/contfu.ttf"
#define PIXFONT "./font/04B.ttf"
#define CALFONT "./font/calibri.ttf"

#define SCOREFILEBINARY "./score"

#define IMAGEJEUDIRECTORY "./img/puzzle/"

#define SONYEP "./sound/yep.wav"
#define SONNOP "./sound/nop.wav"
#define SONCLICBOUTON "./sound/buttonclick.wav"
#define SONLOOSE "./sound/loose.wav"

#define MUSIQUETES "./sound/tes.mp3"
#define MUSIQUECUBAN "./sound/cubanmusic2.mp3"
#define MUSIQUEGALAXY "./sound/galaxy2.mp3"
#define MUSIQUECHIANTE "./sound/chiant.mp3"
#define MUSIQUERICK "./sound/rick.mp3"
#define MUSIQUELOVE "./sound/love.mp3"
#define MUSIQUEWIN "./sound/win.mp3"

#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

#define PSEUDOMAX 20

#define METHODE_RAPIDE 0
#define METHODE_BELLE 1

typedef char T_Nom[PSEUDOMAX];
typedef unsigned long T_Score;

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

SDL_Window* creerFenetre (SDL_Window* fenetre, char* titre, unsigned int tailleX, unsigned int tailleY);
SDL_Surface* chargerImage (SDL_Surface* image, char* chemin);
TTF_Font* chargerPolice (TTF_Font* font, char* chemin, int taille);
void libererPolice (TTF_Font* font);
SDL_Surface* creerTexte (SDL_Surface* surface, short methode, TTF_Font* font, char* texte, SDL_Color couleur);
short hoverMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
short clickMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect) ;
SDL_Rect rangMenu (SDL_Surface* Surface, short rang);
void playmusic (short musique, Mix_Music* gMusic);
void playsound (short sound, Mix_Chunk* gSound);

#endif
