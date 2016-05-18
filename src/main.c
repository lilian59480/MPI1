#include "main.h"

int main (int argc, char** argv)
{
    /* Initialisation des variables */
    SDL_Window* pWindow = NULL;
    TTF_Font* pixFont = NULL;
    TTF_Font* helvFont = NULL;
    TTF_Font* contfuFont = NULL;
    SDL_Event event;
    SDL_Surface* surface = NULL;
    SDL_Surface* titreTTF = NULL;
    SDL_Rect titreRect;
    SDL_Color TitreColor = {0, 0, 0, 0};
    SDL_Color TitreColor2 = {255, 255, 255, 0};
    SDL_Surface* stitreTTF = NULL;
    SDL_Rect stitreRect;
    SDL_Color TitreColors = {255, 255, 255, 0};
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
    T_MScore scores;
    //Pour musique
    short onoff = 0, musique = 3;
    Mix_Music* gMusic = NULL;
    Mix_Chunk* gSound = NULL;
    /* Lecture des parametres envoye par le Shell */
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

    /* Initialisation du sdl_mixer*/
    if ( Mix_OpenAudio ( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        fprintf (stderr, "Echec de l'initialisation de la SDL_mixer :\n %s \n", Mix_GetError() );
        return EXIT_FAILURE;
    }

    /* SDL2 Fonctionel Recuperation d'informations utiles (?) */
    printf ("OS: %s \nRam disponible: %d \n", SDL_GetPlatform(), SDL_GetSystemRAM() );

    /* Recuperation des scores */
    if (!lireMeilleurScore (&scores) )
    {
        /* Pour le moment, on reinitialise, mais dans la suite, il faudra afficher un message d'erreur en cas d'erreur*/
        resetScores (&scores);
    }

    pWindow = creerFenetre (pWindow, TITREJEU, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    helvFont = chargerPolice (helvFont, HELVFONT, 40);
    pixFont = chargerPolice (pixFont, PIXFONT, 70);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 60);
    playmusic (musique, gMusic);

    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                playsound (3, gSound);

                if (clickMenu (helvFont, "Jouer", JouerTTFW, JouerTTFH, event, JouerRect) )
                {
                    fenetreChoixNiveau (pWindow, &scores, gSound);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Meilleur Score", BestTTFW, BestTTFH, event, BestRect) )
                {
                    fenetreMScore (pWindow, &scores, gSound );
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Mot de Passe", PasswordTTFW, PasswordTTFH, event, PasswordRect) )
                {
                    password (gSound, &musique, gMusic, &onoff);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if ( clickMenu (helvFont, "Options", OptionTTFW, OptionTTFH, event, OptionRect) )
                {
                    option (pWindow, &musique, &onoff, gMusic, gSound);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Quitter", QuitterTTFW, QuitterTTFH, event, QuitterRect) )
                {
                    printf ("Good Bye\n");
                    continuer = 0;
                }

                break;

            case SDL_QUIT:
                printf ("Good Bye\n");
                continuer = 0;
                break;

            case SDL_MOUSEMOTION:
                JouerColor.r = hoverMenu (helvFont, "Jouer", JouerTTFW, JouerTTFH, event, JouerRect);
                BestColor.r = hoverMenu (helvFont, "Meilleur Score", BestTTFW, BestTTFH, event, BestRect);
                PasswordColor.r = hoverMenu (helvFont, "Mot de Passe", PasswordTTFW, PasswordTTFH, event, PasswordRect);
                OptionColor.r = hoverMenu (helvFont, "Options", OptionTTFW, OptionTTFH, event, OptionRect);
                QuitterColor.r = hoverMenu (helvFont, "Quitter", QuitterTTFW, QuitterTTFH, event, QuitterRect);
                break;

            default:
                break;
        }

        /* On met une couleur de font */
        surface = SDL_GetWindowSurface (pWindow);
        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 63, 72, 204) );
        titreTTF = creerTexte (titreTTF, METHODE_BELLE, pixFont, TITREJEU, TitreColor);
        titreRect.x = ( (LARGEUR_FENETRE / 2) - (titreTTF->w / 2) ) + 3;
        titreRect.y = (HAUTEUR_FENETRE / 10) + 3;
        SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
        SDL_FreeSurface (titreTTF);
        titreTTF = creerTexte (titreTTF, METHODE_BELLE, pixFont, "Arcade 2i", TitreColor2);
        titreRect.x = (LARGEUR_FENETRE / 2) - (titreTTF->w / 2);
        titreRect.y = HAUTEUR_FENETRE / 10;
        SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
        SDL_FreeSurface (titreTTF);
        stitreTTF = creerTexte (stitreTTF, METHODE_BELLE, contfuFont, "PUZZLE", TitreColors);
        stitreRect.x = (LARGEUR_FENETRE / 2) - (stitreTTF->w / 2);
        stitreRect.y = (2 * HAUTEUR_FENETRE / 10) + 5;
        SDL_BlitSurface (stitreTTF, NULL, surface, &stitreRect);
        SDL_FreeSurface (stitreTTF);
        JouerTTF = creerTexte (JouerTTF, METHODE_RAPIDE, helvFont, "Jouer", JouerColor);
        JouerRect = rangMenu (JouerTTF, 3);
        SDL_BlitSurface (JouerTTF, NULL, surface, &JouerRect);
        SDL_FreeSurface (JouerTTF);
        BestTTF = creerTexte (BestTTF, METHODE_RAPIDE, helvFont, "Meilleur Score", BestColor);
        BestRect = rangMenu (BestTTF, 4);
        SDL_BlitSurface (BestTTF, NULL, surface, &BestRect);
        SDL_FreeSurface (BestTTF);
        PasswordTTF = creerTexte (PasswordTTF, METHODE_RAPIDE, helvFont, "Mot de Passe", PasswordColor);
        PasswordRect = rangMenu (PasswordTTF, 5);
        SDL_BlitSurface (PasswordTTF, NULL, surface, &PasswordRect);
        SDL_FreeSurface (PasswordTTF);
        OptionTTF = creerTexte (OptionTTF, METHODE_RAPIDE, helvFont, "Options", OptionColor);
        OptionRect = rangMenu (OptionTTF, 6);
        SDL_BlitSurface (OptionTTF, NULL, surface, &OptionRect);
        SDL_FreeSurface (OptionTTF);
        QuitterTTF = creerTexte (QuitterTTF, METHODE_RAPIDE, helvFont, "Quitter", QuitterColor);
        QuitterRect = rangMenu (QuitterTTF, 7);
        SDL_BlitSurface (QuitterTTF, NULL, surface, &QuitterRect);
        SDL_FreeSurface (QuitterTTF);
        SDL_UpdateWindowSurface (pWindow);
    }

    SDL_DestroyWindow (pWindow);
    pWindow = NULL;
    libererPolice (helvFont);
    libererPolice (pixFont);
    libererPolice (contfuFont);
    //Liberer musique
    Mix_FreeMusic ( gMusic );
    gMusic = NULL;
    Mix_FreeChunk ( gSound );
    gSound = NULL;
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}

void lireParamShell (int argc, char** argv)
{
    int i = 0;
    T_MScore scores;
    printf ("Nombre de parametre envoye par le Shell: %d \n", argc);

    for (i = 0; i < argc; i++)
    {
        printf ("Parametre %d envoye: %s \n", i, argv[i]);

        if (strcmp (argv[i], "--help") == 0)
        {
            printf ("Liste des commandes disponibles:\n");
            printf ("--help  \t: Affiche cette aide\n");
            printf ("--delete\t: Reset les scores\n");
            exit (EXIT_SUCCESS);
        }
        else if (strcmp (argv[i], "--delete") == 0)
        {
            resetScores (&scores);
            exit (EXIT_SUCCESS);
        }
    }
}