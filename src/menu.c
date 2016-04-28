#include "menu.h"

void fenetreChoixNiveau (SDL_Window* fenetre, T_MScore* score)
{
    /* On n'ouvre pas de nouvelle fenetre, on remplace la fenetre affiché (Pour une belle IHM) */
    TTF_Font* eraserFont = NULL;
    SDL_Color color = {0, 0, 0, 0};
    short continuer = 1;
    short i;
    SDL_Surface* surface = NULL;
    SDL_Surface* surfaceTexte = NULL;
    SDL_Rect rect;
    SDL_Event event;
    eraserFont = chargerPolice (eraserFont, ERASERFONT, 30);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, eraserFont, "Choix du niveau", color);
    rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETRE / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);
    for (i = 0; i < 4; i++)
    {
        //Creer les niveaux
    }
    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
                continuer = 0;
                break;

            case SDL_QUIT:
                printf ("Good Bye\n");
                exit (EXIT_SUCCESS);
                break;

            default:
                break;
        }

        SDL_UpdateWindowSurface (fenetre);
    }
}