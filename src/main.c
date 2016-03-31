#include "main.h"

int main (int argc, char** argv)
{
    /* Initialisation des variables */
    SDL_Window* pWindow = NULL;
    SDL_Surface* imageicone = NULL;
    TTF_Font* eraserFont = NULL;
    SDL_Event event;
    SDL_Surface* surface = NULL;
    SDL_Surface* titreTTF = NULL;
    SDL_Rect titreRect;
    SDL_Color TitreColor = {0, 0, 0, 0};
    SDL_Surface* JouerTTF = NULL;
    SDL_Rect JouerRect;
    SDL_Color JouerColor = {0, 0, 0, 0};
    int JouerTTFW = 0;
    int JouerTTFH = 0;
    SDL_Surface* BestTTF = NULL;
    SDL_Rect BestRect;
    SDL_Color BestColor = {0, 0, 0, 0};
    int BestTTFW = 0;
    int BestTTFH = 0;
    SDL_Surface* PasswordTTF = NULL;
    SDL_Rect PasswordRect;
    SDL_Color PasswordColor = {0, 0, 0, 0};
    int PasswordTTFW = 0;
    int PasswordTTFH = 0;
    SDL_Surface* OptionTTF = NULL;
    SDL_Rect OptionRect;
    SDL_Color OptionColor = {0, 0, 0, 0};
    int OptionTTFW = 0;
    int OptionTTFH = 0;
    SDL_Surface* QuitterTTF = NULL;
    SDL_Rect QuitterRect;
    SDL_Color QuitterColor = {0, 0, 0, 0};
    int QuitterTTFW = 0;
    int QuitterTTFH = 0;
    short continuer = 1;
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
        fprintf (stderr, "Erreur sur l'image %s: %s\n", IMGICONE, IMG_GetError() );
    }
    else
    {
        printf ("Image %s charge\n", IMGICONE);
        SDL_SetWindowIcon (pWindow, imageicone);
    }

    eraserFont = TTF_OpenFont (ERASERFONT, 30);

    if (!eraserFont)
    {
        fprintf (stderr, "Erreur sur la police %s: %s\n", ERASERFONT, TTF_GetError() );
        return EXIT_FAILURE;
    }
    else
    {
        printf ("Police %s charge\n", ERASERFONT);
    }

    /* L'image n'est plus utilise, on peut la supprimer de la memoire */
    SDL_FreeSurface (imageicone);
    /* On met une couleur de font */
    surface = SDL_GetWindowSurface (pWindow);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 63, 72, 204) );

    /* Le titre */
    if (! (titreTTF = TTF_RenderText_Blended (eraserFont, "Puzzle MPI1", TitreColor) ) )
    {
        fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
    }
    else
    {
        titreRect.x = (LARGEUR_FENETRE / 2) - (titreTTF->w / 2);
        titreRect.y = HAUTEUR_FENETRE / 8;
        SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
        SDL_FreeSurface (titreTTF);
    }

    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                printf("%d ",clickMenu (eraserFont, "Jouer", JouerTTFW, JouerTTFH, event, JouerRect));
                printf("%d ",clickMenu (eraserFont, "Meilleur Score", BestTTFW, BestTTFH, event, BestRect));
                printf("%d ",clickMenu (eraserFont, "Mot de Passe", PasswordTTFW, PasswordTTFH, event, PasswordRect));
                printf("%d ",clickMenu (eraserFont, "Options", OptionTTFW, OptionTTFH, event, OptionRect));
                printf("%d\n",clickMenu (eraserFont, "Quitter", QuitterTTFW, QuitterTTFH, event, QuitterRect));
                break;

            case SDL_QUIT:
                printf ("Good Bye\n");
                continuer = 0;
                break;

            case SDL_MOUSEMOTION:
                JouerColor.r = hoverMenu (eraserFont, "Jouer", JouerTTFW, JouerTTFH, event, JouerRect);
                BestColor.r = hoverMenu (eraserFont, "Meilleur Score", BestTTFW, BestTTFH, event, BestRect);
                PasswordColor.r = hoverMenu (eraserFont, "Mot de Passe", PasswordTTFW, PasswordTTFH, event, PasswordRect);
                OptionColor.r = hoverMenu (eraserFont, "Options", OptionTTFW, OptionTTFH, event, OptionRect);
                QuitterColor.r = hoverMenu (eraserFont, "Quitter", QuitterTTFW, QuitterTTFH, event, QuitterRect);
            default:
                break;
        }

        /* On Affiche tout ce qui est a afficher dynamiquement comme le texte */

        /* Jouer */
        if (! (JouerTTF = TTF_RenderText_Solid (eraserFont, "Jouer", JouerColor) ) )
        {
            fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
        }
        else
        {
            JouerRect.x = (LARGEUR_FENETRE / 2) - (JouerTTF->w / 2);
            JouerRect.y = (3 * HAUTEUR_FENETRE) / 8;
            SDL_BlitSurface (JouerTTF, NULL, surface, &JouerRect);
            SDL_FreeSurface (JouerTTF);
        }

        if (! (BestTTF = TTF_RenderText_Solid (eraserFont, "Meilleur Score", BestColor) ) )
        {
            fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
        }
        else
        {
            BestRect.x = (LARGEUR_FENETRE / 2) - (BestTTF->w / 2);
            BestRect.y = (4 * HAUTEUR_FENETRE) / 8;
            SDL_BlitSurface (BestTTF, NULL, surface, &BestRect);
            SDL_FreeSurface (BestTTF);
        }

        if (! (PasswordTTF = TTF_RenderText_Solid (eraserFont, "Mot de passe", PasswordColor) ) )
        {
            fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
        }
        else
        {
            PasswordRect.x = (LARGEUR_FENETRE / 2) - (PasswordTTF->w / 2);
            PasswordRect.y = (5 * HAUTEUR_FENETRE) / 8;
            SDL_BlitSurface (PasswordTTF, NULL, surface, &PasswordRect);
            SDL_FreeSurface (PasswordTTF);
        }

        if (! (OptionTTF = TTF_RenderText_Solid (eraserFont, "Options", OptionColor) ) )
        {
            fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
        }
        else
        {
            OptionRect.x = (LARGEUR_FENETRE / 2) - (OptionTTF->w / 2);
            OptionRect.y = (6 * HAUTEUR_FENETRE) / 8;
            SDL_BlitSurface (OptionTTF, NULL, surface, &OptionRect);
            SDL_FreeSurface (OptionTTF);
        }

        if (! (QuitterTTF = TTF_RenderText_Solid (eraserFont, "Quitter", QuitterColor) ) )
        {
            fprintf (stderr, "Erreur lors de l'ecriture: %s\n", TTF_GetError() );
        }
        else
        {
            QuitterRect.x = (LARGEUR_FENETRE / 2) - (QuitterTTF->w / 2);
            QuitterRect.y = (7 * HAUTEUR_FENETRE) / 8;
            SDL_BlitSurface (QuitterTTF, NULL, surface, &QuitterRect);
            SDL_FreeSurface (QuitterTTF);
        }

        SDL_UpdateWindowSurface (pWindow);
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
