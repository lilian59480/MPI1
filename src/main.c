#include "main.h"

int main (int argc, char** argv)
{
    /* Initialisation des variables */
    SDL_Window* pWindow = NULL;
    SDL_Surface* imageicone = NULL;
    TTF_Font* eraserFont = NULL;
    SDL_Surface* titreTTF = NULL;
    SDL_Event event; 
    SDL_Surface* surface = NULL;
    SDL_Rect dstrect;
    
    short continuer = 1;
    SDL_Color color={255,0,0,0};
    /* Lecture des parametres envoye par le Shell (Inutile pour le moment) */
    lireParamShell (argc, argv);

    /* Initialisation de la SDL2 et SDL_TTF */
    if (SDL_Init (SDL_INIT_VIDEO) != 0 )
    {
        fprintf (stderr, "Echec de l'initialisation de la SDL :\n %s \n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    if (TTF_Init() != 0)
    {
        fprintf (stderr, "Erreur de l'initialisation de la SDL_TTF :\n %s \n", TTF_GetError() );
        return EXIT_FAILURE;
    }

    /* SDL2 Fonctionel Recuperation d'informations utiles (?) */
    printf ("OS: %s \nRam disponible: %d \n", SDL_GetPlatform(), SDL_GetSystemRAM() );
    /* Chargement image */
    imageicone = IMG_Load (IMGICONE);
    /* Creation fenetre */
    pWindow = SDL_CreateWindow ("MPI1 Puzzle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);

    /* Initialisation de la fenetre principale */
    if ( !pWindow )
    {
        fprintf (stderr, "Erreur de creation de la fenetre: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    /* Fenetre Fonctionelle */

    if (!imageicone)
    {
        fprintf (stderr, "Erreur sur l'image %s: %s\n",IMGICONE, IMG_GetError() );
    }
    else
    {
        printf ("Image %s charge\n",IMGICONE);
        SDL_SetWindowIcon (pWindow, imageicone);
    }
    
    eraserFont=TTF_OpenFont(ERASERFONT, 30);
    if(!eraserFont) {
        fprintf (stderr, "Erreur sur la police %s: %s\n",ERASERFONT, TTF_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        printf ("Police %s charge\n",ERASERFONT);
    }
    
    /* L'image n'est plus utilise, on peut la supprimer de la memoire */
    SDL_FreeSurface (imageicone);
    
    surface = SDL_GetWindowSurface(pWindow);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,0xff,0xe4,0xc4));
    
    if(!(titreTTF=TTF_RenderText_Blended(eraserFont,"Hello World!",color))) {
        fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
    } else {
    dstrect.x = (LARGEUR_FENETRE/2)-(titreTTF->w/2);
    dstrect.y = (HAUTEUR_FENETRE/2)-(titreTTF->h/2);
    SDL_BlitSurface(titreTTF,NULL,surface,&dstrect);
    SDL_FreeSurface(titreTTF);
}

    
    SDL_UpdateWindowSurface(pWindow);
    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                printf ("Position du click de souris : (%d ; %d)\n", event.button.x, event.button.y);
                break;

            case SDL_KEYDOWN:
                printf ("Touche appuye: %s\n", SDL_GetKeyName (event.key.keysym.sym) );
                break;

            case SDL_QUIT:
                printf ("Good Bye\n");
                continuer = 0;
                break;

            default:
                break;
        }
    }

    SDL_DestroyWindow (pWindow);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}

void lireParamShell (int argc, char** argv)
{
    int i = 0;
    printf ("Nombre de parametre envoye par le Shell: %d \n", argc);

    for (i = 0; i < argc; i++)
    {
        printf ("Parametre %d envoye: %s \n", i, argv[i]);
    }
}
