#include "common.h"

SDL_Window* creerFenetre (SDL_Window* fenetre, char* titre, unsigned int tailleX, unsigned int tailleY)
{
    SDL_Surface* imageicone = NULL;
    fenetre = SDL_CreateWindow (titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tailleX, tailleY, SDL_WINDOW_SHOWN);

    if ( !fenetre )
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur de creation de la fenetre", SDL_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    imageicone = chargerImage (imageicone, IMGICONE);
    SDL_SetWindowIcon (fenetre, imageicone);
    SDL_FreeSurface (imageicone);
    return fenetre;
}

SDL_Surface* chargerImage (SDL_Surface* image, char* chemin)
{
    image = IMG_Load (chemin);

    if (!image)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur sur l'image", IMG_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    printf ("Image %s charge\n", chemin);
    return image;
}

TTF_Font* chargerPolice (TTF_Font* font, char* chemin, int taille)
{
    font = TTF_OpenFont (chemin, taille);

    if (!font)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur sur la police", TTF_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    printf ("Police %s charge\n", chemin);
    return font;
}

void libererPolice (TTF_Font* font)
{
    TTF_CloseFont (font);
}

SDL_Surface* creerTexte (SDL_Surface* surface, short methode, TTF_Font* font, char* texte, SDL_Color couleur)
{
    switch (methode)
    {
        case METHODE_BELLE:
            surface = TTF_RenderText_Blended (font, texte, couleur);
            break;

        case METHODE_RAPIDE:
        default:
            surface = TTF_RenderText_Solid (font, texte, couleur);
            break;
    }

    if (!surface)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur de creation du texte", TTF_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    return surface;
}

short hoverMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect)
{
    TTF_SizeText (Font, String, &TTFW, &TTFH);

    if (event.motion.x > Rect.x)
    {
        if (event.motion.y > Rect.y)
        {
            if (event.motion.x < (Rect.x + TTFW) )
            {
                if (event.motion.y < (Rect.y + TTFH) )
                {
                    return 255;
                }
            }
        }
    }

    return 0;
}

short clickMenu (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect)
{
    TTF_SizeText (Font, String, &TTFW, &TTFH);

    if (event.button.x > Rect.x)
    {
        if (event.button.y > Rect.y)
        {
            if (event.button.x < (Rect.x + TTFW) )
            {
                if (event.button.y < (Rect.y + TTFH) )
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

SDL_Rect rangMenu (SDL_Surface* Surface, short rang)
{
    SDL_Rect Rect = {0, 0, 0, 0};
    Rect.x = (LARGEUR_FENETRE / 2) - (Surface->w / 2);
    Rect.y = (rang * HAUTEUR_FENETRE) / 8;
    return Rect;
}

void playmusic (short musique, Mix_Music* gMusic)
{
    //Load music
    switch (musique)
    {
        case 1 :
            gMusic = Mix_LoadMUS ( MUSIQUETES );
            break;

        case 2 :
            gMusic = Mix_LoadMUS ( MUSIQUECUBAN );
            break;

        case 3 :
            gMusic = Mix_LoadMUS ( MUSIQUEGALAXY );
            break;

        case 4 :
            gMusic = Mix_LoadMUS ( MUSIQUECHIANTE );
            break;

        case 5 :
            gMusic = Mix_LoadMUS ( MUSIQUERICK );
            break;

        case 6 : //musique victoire
            gMusic = Mix_LoadMUS ( MUSIQUEWIN );
            break;

        case 7 :
            gMusic = Mix_LoadMUS ( MUSIQUELOVE );
            break;

        case 8 :
            gMusic = Mix_LoadMUS ( MUSIQUENYANCAT );
            break;
    }

    if ( gMusic == NULL )
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur du gestionnaire de son", Mix_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    Mix_PlayMusic ( gMusic, -1 );
    return;
}

void playsound (short sound, Mix_Chunk* gSound)
{
    //Load sfx
    switch (sound)
    {
        case 1 :
            gSound = Mix_LoadWAV ( SONYEP );
            break;

        case 2 :
            gSound = Mix_LoadWAV ( SONNOP );
            break;

        case 3 :
            gSound = Mix_LoadWAV ( SONCLICBOUTON );
            break;

        case 4 : //son defaite
            gSound = Mix_LoadWAV (SONLOOSE);
            break;
    }

    if ( gSound == NULL )
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur du gestionnaire de son", Mix_GetError() , NULL);
        exit (EXIT_FAILURE);
    }

    Mix_PlayChannel ( -1, gSound, 0 );
    return;
}