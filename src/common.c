#include "common.h"

SDL_Window* creerFenetre (SDL_Window* fenetre, char* titre)
{
    SDL_Surface* imageicone = NULL;
    fenetre = SDL_CreateWindow (titre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);

    if ( !fenetre )
    {
        fprintf (stderr, "Erreur de creation de la fenetre: %s\n", SDL_GetError() );
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
        fprintf (stderr, "Erreur sur l'image %s: %s\n", chemin, IMG_GetError() );
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
        fprintf (stderr, "Erreur sur la police %s: %s\n", chemin, TTF_GetError() );
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
        fprintf (stderr, "Erreur lors de l'ecriture du texte: %s\n", TTF_GetError() );
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

