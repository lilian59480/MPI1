#include "option.h"

int option (SDL_Window* fenetreoption, short* musique, short* onoff, Mix_Music* gMusic, Mix_Chunk* gSound )
{
    SDL_bool done = SDL_FALSE;
    SDL_Rect rect;
    SDL_Event ev;
    SDL_Color noir = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 0, 0};
    SDL_Color blanc = {255, 255, 255, 0};
    SDL_Surface* txtTTF = NULL;
    SDL_Rect txtRect;
    SDL_Surface* onTTF = NULL;
    SDL_Rect onRect;
    int onTTFW = 0;
    int onTTFH = 0;
    SDL_Surface* offTTF = NULL;
    SDL_Rect offRect;
    int offTTFW = 0;
    int offTTFH = 0;
    SDL_Surface* RetourTTF = NULL;
    SDL_Rect RetourRect;
    SDL_Color RetourColor = {0, 0, 0, 0};
    int RetourTTFW = 0;
    int RetourTTFH = 0;
    SDL_Surface* Mus1TTF = NULL;
    SDL_Rect Mus1Rect;
    int Mus1TTFW = 0;
    int Mus1TTFH = 0;
    SDL_Surface* Mus2TTF = NULL;
    SDL_Rect Mus2Rect;
    int Mus2TTFW = 0;
    int Mus2TTFH = 0;
    SDL_Surface* Mus3TTF = NULL;
    SDL_Rect Mus3Rect;
    int Mus3TTFW = 0;
    int Mus3TTFH = 0;
    SDL_Surface* Mus4TTF = NULL;
    SDL_Rect Mus4Rect;
    int Mus4TTFW = 0;
    int Mus4TTFH = 0;
    SDL_Surface* delTTF = NULL;
    SDL_Rect delRect;
    SDL_Color delColor = {0, 0, 0, 0};
    int delTTFW = 0;
    int delTTFH = 0;
    SDL_Surface* CreditsTTF = NULL;
    SDL_Rect CreditsRect;
    SDL_Color CreditsColor = {0, 0, 0, 0};
    int CreditsTTFW = 0;
    int CreditsTTFH = 0;
    TTF_Font* contfuFont = NULL;
    TTF_Font* helvFont = NULL;
    SDL_Surface* surface = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 35);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 60);
    SDL_Surface* surfaceTexte = NULL;

    while (!done)
    {
        SDL_WaitEvent (&ev);

        switch (ev.type)
        {
            case SDL_QUIT : // Ne marche pas, je sais pas pourquoi
                printf ("Good bye\n");
                done = SDL_TRUE;
                break;

            case SDL_KEYDOWN :
                if (ev.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = SDL_TRUE;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                playsound (3, gSound);

                if (clickMenu (helvFont, "Retour", RetourTTFW, RetourTTFH, ev, RetourRect) )
                {
                    done = SDL_TRUE;
                }
                else if (clickMenu (helvFont, "Credits", CreditsTTFW, CreditsTTFH, ev, CreditsRect) )
                {
                    printf ("Credits\n");
                    credits();
                }
                else if (clickMenu (helvFont, "Suprimer les highscores", delTTFW, delTTFH, ev, delRect) )
                {
                    T_MScore score;
                    resetScores (&score);
                }
                else if (clickMenu (helvFont, "Epic", Mus1TTFW, Mus1TTFH, ev, Mus1Rect) && (*musique != 1) )
                {
                    *musique = 1;

                    if (*onoff == 0)
                    {
                        playmusic (*musique, gMusic);
                    }
                }
                else if (clickMenu (helvFont, "Jazz", Mus2TTFW, Mus2TTFH, ev, Mus2Rect) && (*musique != 2) )
                {
                    *musique = 2;

                    if (*onoff == 0)
                    {
                        playmusic (*musique, gMusic);
                    }
                }
                else if (clickMenu (helvFont, "Casu", Mus3TTFW, Mus3TTFH, ev, Mus3Rect) && (*musique != 3) )
                {
                    *musique = 3;

                    if (*onoff == 0)
                    {
                        playmusic (*musique, gMusic);
                    }
                }
                else if (clickMenu (helvFont, "Enervant", Mus4TTFW, Mus4TTFH, ev, Mus4Rect) && (*musique != 4) )
                {
                    *musique = 4;

                    if (*onoff == 0)
                    {
                        playmusic (*musique, gMusic);
                    }
                }
                else if (clickMenu (helvFont, "Oui", onTTFW, onTTFH, ev, onRect) && (*onoff != 1) )
                {
                    *onoff = 1;
                    Mix_HaltMusic();
                }
                else if (clickMenu (helvFont, "Non", offTTFW, offTTFH, ev, offRect) && (*onoff != 0) )
                {
                    *onoff = 0;
                    playmusic (*musique, gMusic);
                }

                break;

            case SDL_MOUSEMOTION:
                delColor.r = hoverMenu (helvFont, "Suprimer les highscores", delTTFW, delTTFH, ev, delRect);
                RetourColor.r = hoverMenu (helvFont, "Retour", RetourTTFW, RetourTTFH, ev, RetourRect);
                CreditsColor.r = hoverMenu (helvFont, "Credits", CreditsTTFW, CreditsTTFH, ev, CreditsRect);
                break;
        }

        surface = SDL_GetWindowSurface (fenetreoption);
        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 252, 220, 18) );
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "Options", blanc);
        rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
        rect.y = HAUTEUR_FENETRE / 12;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        RetourTTF = creerTexte (RetourTTF, METHODE_RAPIDE, helvFont, "Retour", RetourColor);
        RetourRect.x = (LARGEUR_FENETRE / 2) - (RetourTTF->w / 2);
        RetourRect.y = (7 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (RetourTTF, NULL, surface, &RetourRect);
        SDL_FreeSurface (RetourTTF);
        Mus1TTF = creerTexte (Mus1TTF, METHODE_RAPIDE, helvFont, "Epic", (*musique == 1) ? rouge : noir);
        Mus1Rect.x = (LARGEUR_FENETRE / 5) - (Mus1TTF->w / 2);
        Mus1Rect.y = (3 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (Mus1TTF, NULL, surface, &Mus1Rect);
        SDL_FreeSurface (Mus1TTF);
        Mus2TTF = creerTexte (Mus2TTF, METHODE_RAPIDE, helvFont, "Jazz", (*musique == 2) ? rouge : noir);
        Mus2Rect.x = (2 * LARGEUR_FENETRE / 5) - (Mus2TTF->w / 2);
        Mus2Rect.y = (3 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (Mus2TTF, NULL, surface, &Mus2Rect);
        SDL_FreeSurface (Mus2TTF);
        Mus3TTF = creerTexte (Mus3TTF, METHODE_RAPIDE, helvFont, "Casu", (*musique == 3) ? rouge : noir);
        Mus3Rect.x = (3 * LARGEUR_FENETRE / 5) - (Mus3TTF->w / 2);
        Mus3Rect.y = (3 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (Mus3TTF, NULL, surface, &Mus3Rect);
        SDL_FreeSurface (Mus3TTF);
        Mus4TTF = creerTexte (Mus4TTF, METHODE_RAPIDE, helvFont, "Enervant", (*musique == 4) ? rouge : noir);
        Mus4Rect.x = (4 * LARGEUR_FENETRE / 5) - (Mus4TTF->w / 2);
        Mus4Rect.y = (3 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (Mus4TTF, NULL, surface, &Mus4Rect);
        SDL_FreeSurface (Mus4TTF);
        delTTF = creerTexte (delTTF, METHODE_RAPIDE, helvFont, "Supprimer les highscores", delColor);
        delRect.x = (LARGEUR_FENETRE / 2) - (delTTF->w / 2);
        delRect.y = (HAUTEUR_FENETRE) / 4;
        SDL_BlitSurface (delTTF, NULL, surface, &delRect);
        SDL_FreeSurface (delTTF);
        CreditsTTF = creerTexte (CreditsTTF, METHODE_RAPIDE, helvFont, "Credits", CreditsColor);
        CreditsRect.x = (LARGEUR_FENETRE / 2) - (CreditsTTF->w / 2);
        CreditsRect.y = (5 * HAUTEUR_FENETRE) / 8;
        SDL_BlitSurface (CreditsTTF, NULL, surface, &CreditsRect);
        SDL_FreeSurface (CreditsTTF);
        txtTTF = creerTexte (txtTTF, METHODE_RAPIDE, helvFont, "Desactiver musique", noir);
        txtRect.x = (LARGEUR_FENETRE / 3) - (txtTTF->w / 2);
        txtRect.y = (HAUTEUR_FENETRE) / 2;
        SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
        SDL_FreeSurface (txtTTF);
        onTTF = creerTexte (onTTF, METHODE_RAPIDE, helvFont, "Oui", (*onoff == 1) ? rouge : noir);
        onRect.x = (7 * LARGEUR_FENETRE / 10) - (onTTF->w / 2);
        onRect.y = (HAUTEUR_FENETRE) / 2;
        SDL_BlitSurface (onTTF, NULL, surface, &onRect);
        SDL_FreeSurface (onTTF);
        offTTF = creerTexte (offTTF, METHODE_RAPIDE, helvFont, "Non", (*onoff == 0) ? rouge : noir);
        offRect.x = (8 * LARGEUR_FENETRE / 10) - (offTTF->w / 2);
        offRect.y = (HAUTEUR_FENETRE) / 2;
        SDL_BlitSurface (offTTF, NULL, surface, &offRect);
        SDL_FreeSurface (offTTF);
        SDL_UpdateWindowSurface (fenetreoption);
    }

    libererPolice (helvFont);
    libererPolice (contfuFont);
    return 0;
}

void credits()
{
    SDL_Window* fenetre = NULL;
    SDL_bool done = SDL_FALSE;
    SDL_Event ev;
    SDL_Rect rect;
    SDL_Surface* txtTTF = NULL;
    SDL_Rect txtRect;
    SDL_Color blanc = {255, 255, 255, 0};
    SDL_Color rouge = {255, 0, 0, 0};
    TTF_Font* contfuFont = NULL;
    TTF_Font* contfuFont2 = NULL;
    TTF_Font* calFont = NULL;
    SDL_Surface* surface = NULL;
    calFont = chargerPolice (calFont, CALFONT, 20);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 60);
    contfuFont2 = chargerPolice (contfuFont, CONTFUFONT, 30);
    SDL_Surface* surfaceTexte = NULL;
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 0, 0, 0) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "Credits", blanc);
    rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETRE / 12;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Arcade 2i Puzzle a ete cree par PETITPAS Lilian et TERNISIEN", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 3 * HAUTEUR_FENETRE / 12 ;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Thomas dans le cadre d'un projet informatique en premiere", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 3 * HAUTEUR_FENETRE / 12 + 25;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "annee a Centrale Lille formation IG2I", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 3 * HAUTEUR_FENETRE / 12 + 50;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, contfuFont2, "Musiques", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 5 * HAUTEUR_FENETRE / 12;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "BO de Skyrim, Oblivion, Morrowind - Jeremy Soule", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Subway Harry - Poncho Sanchez", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 25;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "March for Koala, Old School Game - The Seatbelts", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 50;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Throwback Galaxy - Mario Galaxy Orchestra", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 75;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Final Fantasy VI Victory Franfare - Nobuo Uematsu", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 100;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont, "Never Gonna Give You Up - Rick Astley", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 125;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    txtTTF = creerTexte (txtTTF, METHODE_BELLE, calFont,             "What is         - Haddaway", blanc);
    txtRect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    txtRect.y = 6 * HAUTEUR_FENETRE / 12 + 150;
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, calFont, "              love", rouge);
    rect.x = (LARGEUR_FENETRE / 2) - (txtTTF->w / 2);
    rect.y = 6 * HAUTEUR_FENETRE / 12 + 150;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    SDL_UpdateWindowSurface (fenetre);

    while (!done)
    {
        SDL_WaitEvent (&ev);

        switch (ev.type)
        {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;

            case SDL_KEYDOWN :
                done = SDL_TRUE;
                break;

            case SDL_MOUSEBUTTONDOWN :
                done = SDL_TRUE;
                break;
        }
    }

    libererPolice (calFont);
    libererPolice (contfuFont);
    SDL_DestroyWindow (fenetre);
}