#include "best.h"

void fenetreMScore (SDL_Window* fenetre, T_MScore* score, Mix_Chunk* gSound)
{
    /* On n'ouvre pas de nouvelle fenetre, on remplace la fenetre affiché (Pour une belle IHM) */
    SDL_Color color = {0, 0, 0, 0};
    SDL_Color color2 = {255, 255, 255, 0};
    short continuer = 1;
    SDL_Surface* surface = NULL;
    SDL_Surface* surfaceTexte = NULL;
    SDL_Rect rect;
    SDL_Event event;
    char Nom[10];
    short i = 0;
    TTF_Font* contfuFont = NULL;
    TTF_Font* helvFont = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 35);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 60);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "Meilleurs scores", color2);
    rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETRE / 12;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);

    for (i = 0; i < 5; i++)
    {
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, score->Scores[i].Nom , color);
        rect = rangScores (surfaceTexte, i + 3, PLACEGAUCHE);
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        surfaceTexte = NULL;
        sprintf (Nom, "%lu", score->Scores[i].Score );
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, Nom , color);
        rect = rangScores (surfaceTexte, i + 3, PLACEDROITE);
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        surfaceTexte = NULL;
    }

    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, "Appuyer pour quitter", color);
    rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
    rect.y = (7 * HAUTEUR_FENETRE) / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);

    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                playsound (3, gSound);

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

short ecrireMeilleurScore (T_MScore* scores)
{
    FILE* fichier = NULL;
    fichier = fopen (SCOREFILEBINARY, "wb");

    if (fichier == NULL)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur interne", strerror (errno), NULL);
        return 0;
    }

    fwrite (scores, sizeof (T_MScore), 1, fichier);
    fclose (fichier);
    printf ("Les scores ont bien ete enregistre\n");
    return 1;
}

short lireMeilleurScore (T_MScore* scores)
{
    FILE* fichier = NULL;
    fichier = fopen (SCOREFILEBINARY, "rb");

    if (fichier == NULL)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Lecture des scores", strerror (errno), NULL);
        return 0;
    }

    fread (scores, sizeof (T_MScore), 1, fichier);

    if (ferror (fichier) )
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Lecture des scores", strerror (errno), NULL);
        fclose (fichier);
        return 0;
    }

    fclose (fichier);
    printf ("Les scores ont ete charge\n");
    return 1;
}


void resetScores (T_MScore* score)
{
    printf ("Remise a zero des scores\n");
    score->Scores[0].Score = 10000;
    score->Scores[1].Score = 1000;
    score->Scores[2].Score = 100;
    score->Scores[3].Score = 10;
    score->Scores[4].Score = 1;
    strcpy (score->Scores[0].Nom, "hardcore");
    strcpy (score->Scores[1].Nom, "JeSuisUneAutreChai2");
    strcpy (score->Scores[2].Nom, "JeSuisUneChaine   3");
    strcpy (score->Scores[3].Nom, "Petite Chaine");
    strcpy (score->Scores[4].Nom, "Aa?");

    if (ecrireMeilleurScore (score) )
    {
        printf ("Les scores ont ete remis a zero\n");
    }
    else
    {
        printf ("Les scores n'ont pas ete remis a zero\nEssayer de corriger le probleme en supprimant le fichier %s\n", SCOREFILEBINARY);
    }
}

SDL_Rect rangScores (SDL_Surface* Surface, short rang, short place)
{
    SDL_Rect Rect = {0, 0, 0, 0};

    if (place == PLACEGAUCHE)
    {
        Rect.x = (LARGEUR_FENETRE / 4) - (Surface->w / 2);
    }
    else
    {
        Rect.x = ( (3 * LARGEUR_FENETRE) / 4) - (Surface->w / 2);
    }

    Rect.y = (rang * HAUTEUR_FENETRE) / 9;
    return Rect;
}