#include "jeu.h"

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte, short r, short v, short b, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff )
{
    SDL_Window* fenetre = NULL;
    SDL_Surface* surface = NULL;
    SDL_Surface* image = NULL;
    SDL_bool continuer = SDL_FALSE;
    T_Cases plateau;
    int i=0, j=0,iselect=0,jselect=0;
    char chemin[100];
    SDL_Event event;
    SDL_Rect rectImage;
    SDL_Rect rect;
    SDL_Rect rect2;
    int hauteur;
    int taillecaseplateau = 0;
    int value;
    int positionsourisx = 0;
    int positionsourisy = 0;
    int caseclicx = 0;
    int caseclicy = 0;
    
    SDL_Surface* QuitterTTF = NULL;
    SDL_Rect QuitterRect;
    SDL_Color QuitterColor = {0, 0, 0, 0};
    int QuitterTTFW = 0;
    int QuitterTTFH = 0;
    short win;
    SDL_Surface* cheatTTF = NULL;
    SDL_Rect cheatRect;
    SDL_Color cheatColor = {0, 0, 0, 0};
    int cheatTTFW = 0;
    int cheatTTFH = 0;
    SDL_Surface* tempsTTF = NULL;
    SDL_Rect tempsRect;
    SDL_Color tempsColor = {0, 0, 0, 0};
    SDL_Surface* coupsTTF = NULL;
    SDL_Rect coupsRect;
    SDL_Color coupsColor = {0, 0, 0, 0};
    
    
    
    TTF_Font* helvFont = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 40);

    switch (difficulte)
    {
        case 0:
            plateau.taillexy = 4;
            taillecaseplateau = 100;
            break;

        case 1:
            plateau.taillexy = 8;
            taillecaseplateau = 50;
            break;

        case 3:
            plateau.taillexy = 10;
            taillecaseplateau = 40;
            break;

        default:
            fprintf (stderr, "Difficulte inconnue : %d\n", difficulte );
            exit (EXIT_FAILURE);
            break;
    }

    melangercase (&plateau);
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE * 2, 3*HAUTEUR_FENETRE/2);
    surface = SDL_GetWindowSurface (fenetre);
    verifierCouleur (&r, &v, &b);

    if (snprintf (chemin, 95, "%s%s0.png", IMAGEJEUDIRECTORY, cheminniveau) < 0)
    {
        fprintf (stderr, "Erreur Inconnu!" );
        exit (EXIT_FAILURE);
    }

    image = chargerImage (image, chemin);

    while (!continuer)
    {
        SDL_WaitEvent (&event);
        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, r, v, b) );
        rectImage.x = 2 * LARGEUR_FENETRE - image->w - 100;
        hauteur = (HAUTEUR_FENETRE / 2) - (image->h / 2);
        rectImage.y = hauteur;
        SDL_BlitSurface (image, NULL, surface, &rectImage);
        rect2.w = taillecaseplateau;
        rect2.h = taillecaseplateau;
        QuitterTTF = creerTexte (QuitterTTF, METHODE_RAPIDE, helvFont, "Abandonner", QuitterColor);
        QuitterRect.x = (6*LARGEUR_FENETRE / 4) - (QuitterTTF->w / 2) + 20;
        QuitterRect.y = (4 * HAUTEUR_FENETRE) / 4 +20;
        SDL_BlitSurface (QuitterTTF, NULL, surface, &QuitterRect);
        SDL_FreeSurface (QuitterTTF);
        coupsTTF = creerTexte (coupsTTF, METHODE_RAPIDE, helvFont, "Nombre de coups : ", coupsColor);
        coupsRect.x = 100;
        coupsRect.y = (4 * HAUTEUR_FENETRE) / 4 +20;
        SDL_BlitSurface (coupsTTF, NULL, surface, &coupsRect);
        SDL_FreeSurface (coupsTTF);
        tempsTTF = creerTexte (tempsTTF, METHODE_RAPIDE, helvFont, "Temps : ", tempsColor);
        tempsRect.x = 100;
        tempsRect.y = (4 * HAUTEUR_FENETRE) / 4 + 100;
        SDL_BlitSurface (tempsTTF, NULL, surface, &tempsRect);
        SDL_FreeSurface (tempsTTF);
        cheatTTF = creerTexte (cheatTTF, METHODE_RAPIDE, helvFont, "cheat", cheatColor);
        cheatRect.x = (6*LARGEUR_FENETRE / 4) - (cheatTTF->w / 2) + 20;
        cheatRect.y = (4 * HAUTEUR_FENETRE) / 4 +50;
        SDL_BlitSurface (cheatTTF, NULL, surface, &cheatRect);
        SDL_FreeSurface (cheatTTF);

        for (i = 0; i < plateau.taillexy; i++)
        {
            for (j = 0; j < plateau.taillexy; j++)
            {
                value = plateau.plateau[i][j];

                if (value == plateau.selectionne)
                {
                    rect.x = positionsourisx;
                    rect.y = positionsourisy;
                }
                else
                {
                    rect.x = 100 + (taillecaseplateau * (i) );
                    rect.y = hauteur + (taillecaseplateau * (j) );
                }

                rect2.x = 0 + (taillecaseplateau * (value / plateau.taillexy) );
                rect2.y = 0 + (taillecaseplateau * (value % plateau.taillexy) );
                SDL_BlitSurface (image, &rect2, surface, &rect);
            }
        }

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            playsound (3, gSound);
                if (event.button.x > 100 && event.button.x < (100 + (image->w) ) )
                {
                    if (event.button.y > hauteur && event.button.y < (hauteur + (image->h) ) )
                    {
                        caseclicx = (event.button.x - 100) / taillecaseplateau;
                        caseclicy = (event.button.y - hauteur) / taillecaseplateau;

                        if (plateau.selectionne == -1)
                        {
                            for (i = 0; i < plateau.taillexy; i++)
                            {
                                for (j = 0; j < plateau.taillexy; j++)
                                {
                                    value = plateau.plateau[i][j];
                                    if (i == caseclicx && j == caseclicy)
                                    {
                                        plateau.selectionne = value;
                                    }
                                }
                            }

                            printf ("Selection d'une case: %d,%d\n", caseclicx, caseclicy);
                        }
                        else
                        {
                            for (i = 0; i < plateau.taillexy; i++)
                            {
                                for (j = 0; j < plateau.taillexy; j++)
                                {
                                    if (plateau.plateau[i][j] == plateau.selectionne)
                                    {
                                        iselect = i;
                                        jselect = j;
                                    }
                                }
                            }
                            
                            
                            for (i = 0; i < plateau.taillexy; i++)
                            {
                                for (j = 0; j < plateau.taillexy; j++)
                                {
                                    value = plateau.plateau[i][j];
                                    if (i == caseclicx && j == caseclicy)
                                    {
                                        if (plateau.selectionne == value)
                                        {
                                            plateau.selectionne = -1;
                                        }
                                        else {
                                            plateau.plateau[iselect][jselect] = plateau.plateau[i][j];
                                            plateau.plateau[i][j] = plateau.selectionne;
                                            plateau.selectionne = value;
                                        }
                                    }
                                }
                            }
                            printf ("Depos d'une case: %d,%d\n", caseclicx, caseclicy);
                            _debugT_Cases (&plateau);
                            if(validerCase(&plateau) && plateau.selectionne == -1)
                            {
                                win = 1;
                                continuer = SDL_TRUE;
                            }
                        }
                    }
                }
                if (clickMenu (helvFont, "Abandonner", QuitterTTFW, QuitterTTFH, event, QuitterRect) )
                {
                    continuer = SDL_TRUE;
                    win = 0;
                }
                if (clickMenu (helvFont, "cheat", cheatTTFW, cheatTTFH, event, cheatRect) )
                {
                    continuer = SDL_TRUE;
                    win = 1;
                }
                break;

            case SDL_KEYDOWN :
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = SDL_TRUE;

                    default:
                        break;
                }

                break;

            case SDL_QUIT:
                continuer = SDL_TRUE;
                break;

            case SDL_MOUSEMOTION:
                positionsourisx = event.motion.x;
                positionsourisy = event.motion.y;
                QuitterColor.r = hoverMenu (helvFont, "Abandonner", QuitterTTFW, QuitterTTFH, event, QuitterRect);
                cheatColor.r = hoverMenu (helvFont, "cheat", cheatTTFW, cheatTTFH, event, cheatRect);
                break;

            default:
                break;
        }

        drawGrille (surface, 100, hauteur, taillecaseplateau, plateau.taillexy );
        SDL_UpdateWindowSurface (fenetre);
    }
    
    

    libererPolice (helvFont);
    SDL_DestroyWindow (fenetre);
    fenetre = NULL;
    if(win==1) {
        printf("C'est gagne\n");
        SDL_Delay(50);
        wine(score,gSound,gMusic, musique, onoff);
        
    }
    else if (win == 0) {
        printf("C'est perdu\n");
        loose(gSound);
    }
    return;
}

void melangercase (T_Cases* plateau )
{
    int i;
    T_Case a[TAILLEPLATEAUMAX * TAILLEPLATEAUMAX];
    int taille = plateau->taillexy;
    int n = taille * taille;

    if (n > (TAILLEPLATEAUMAX * TAILLEPLATEAUMAX) )
    {
        fprintf (stderr, "N est trop grand! :\n %d>%d \n", n, TAILLEPLATEAUMAX );
        exit (EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
    {
        a[i] = i;
    }

    srand (time (NULL) );

    for (i = 0; i < n - 2; i++)
    {
        int j;
        j = rand() % (n - i);
        T_Case k;
        k = a[i];
        a[i] = a[i + j];
        a[i + j] = k;
    }

    int j = 0;
    int k = 0;

    for (i = 0; i < (taille * taille) ; i++, k++)
    {
        if (k >= taille)
        {
            k = 0;
            j++;
        }

        plateau->plateau[j][k] = a[i];
    }

    plateau->selectionne = -1;
    _debugT_Cases (plateau);
}

void _debugT_Cases (T_Cases* plateau)
{
    int i;
    int j;

    for (i = 0; i < plateau->taillexy; i++)
    {
        for (j = 0; j < plateau->taillexy; j++)
        {
            printf ("{%d,%d} = %d\t%d,%d\n", i, j, plateau->plateau[i][j], plateau->plateau[i][j] / 4, plateau->plateau[i][j] % 4);
        }
    }
}

short validerCase (T_Cases* plateau)
{
    int i;
    int j;
    int k = 0;

    for (i = 0; i < plateau->taillexy; i++)
    {
        for (j = 0; j < plateau->taillexy; j++)
        {
            if (k == plateau->plateau[i][j] )
            {
                k++;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

void verifierCouleur (short* r, short* v, short* b)
{
    if (* (r) < 0 || * (r) > 255)
    {
        * (r) = 255;
    }

    if (* (v) < 0 || * (v) > 255)
    {
        * (v) = 0;
    }

    if (* (b) < 0 || * (b) > 255)
    {
        * (b) = 255;
    }
}

void drawEmptyRect (SDL_Surface* surf, int posX, int posY, int width)
{
    SDL_Rect ligneHaut;
    ligneHaut.x = posX - 1;
    ligneHaut.y = posY - 1;
    ligneHaut.w = width;
    ligneHaut.h = 1;
    SDL_FillRect (surf, &ligneHaut, SDL_MapRGB (surf->format, 255, 255, 255) );
    SDL_Rect ligneDroite;
    ligneDroite.x = posX + width - 1;
    ligneDroite.y = posY - 1;
    ligneDroite.w = 1;
    ligneDroite.h = width;
    SDL_FillRect (surf, &ligneDroite, SDL_MapRGB (surf->format, 255, 255, 255) );
    SDL_Rect ligneGauche;
    ligneGauche.x = posX - 1;
    ligneGauche.y = posY - 1;
    ligneGauche.w = 1;
    ligneGauche.h = width;
    SDL_FillRect (surf, &ligneGauche, SDL_MapRGB (surf->format, 255, 255, 255) );
    SDL_Rect ligneBas;
    ligneBas.x = posX - 1;
    ligneBas.y = posY + width - 1;
    ligneBas.w = width;
    ligneBas.h = 1;
    SDL_FillRect (surf, &ligneBas, SDL_MapRGB (surf->format, 255, 255, 255) );
}


void drawGrille (SDL_Surface* surface, int posX, int posY, int taillecase, int nbcase)
{
    short i, j;

    for (i = 0; i < nbcase; i++)
        for (j = 0; j < nbcase; j++)
        {
            drawEmptyRect (surface, i * taillecase + posX, j * taillecase + posY, taillecase);
        }
}

void wine (T_MScore* score, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff)
{
    SDL_Window* fenetre = NULL;
    SDL_Surface* surface = NULL;
    char texte[PSEUDOMAX] = {0};
    size_t passlen = 0, l;
    SDL_bool done = SDL_FALSE;
    SDL_Rect rect;
    SDL_Event ev;
    SDL_Surface* ValiderTTF = NULL;
    SDL_Rect ValiderRect;
    SDL_Color ValiderColor = {0, 0, 0, 0};
    int ValiderTTFW = 0;
    int ValiderTTFH = 0;
    SDL_Surface* pseudoTTF = NULL;
    SDL_Rect pseudoRect;
    SDL_Color pseudoColor = {0, 0, 0, 0};
    TTF_Font* helvFont = NULL;
    TTF_Font* pixFont = NULL;
    TTF_Font* contfuFont = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 40);
    pixFont = chargerPolice (pixFont, PIXFONT, 100);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 40);
    SDL_Surface* surfaceTexte = NULL;
    SDL_Color color2 = {255, 255, 255, 0};
    SDL_Color color = {0, 0, 0, 0};
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    SDL_UpdateWindowSurface (fenetre);
    playmusic (6, gMusic);
    
    
    SDL_StartTextInput();

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
                if (ev.key.keysym.sym == SDLK_BACKSPACE && passlen > 0)
                {
                    texte[passlen - 1] = 0;
                    passlen--;
                    puts (texte);
                }
                else if (ev.key.keysym.sym == SDLK_ESCAPE)
                {
                    done = SDL_TRUE;
                }
                else if (ev.key.keysym.sym == SDLK_RETURN)
                {
                    printf ("testvalider\n");
                }

                break;

            case SDL_TEXTINPUT :
                l = strlen (ev.text.text);
                strncpy (texte + passlen, ev.text.text, PSEUDOMAX - 1 - passlen);
                passlen += l;

                if (passlen > PSEUDOMAX - 1)
                {
                    passlen = PSEUDOMAX - 1;
                }

                puts (texte);
                break;

            case SDL_MOUSEBUTTONDOWN:
                playsound (3, gSound);

                if (clickMenu (helvFont, "Valider", ValiderTTFW, ValiderTTFH, ev, ValiderRect) )
                {
                    printf ("testvalider\n");
                    ev.type = SDL_KEYDOWN;
                    ev.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&ev);
                }


                break;

            case SDL_MOUSEMOTION:
                ValiderColor.r = hoverMenu (helvFont, "Valider", ValiderTTFW, ValiderTTFH, ev, ValiderRect);
                break;
        }

        surface = SDL_GetWindowSurface (fenetre);
        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 75, 220, 56) );
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, pixFont, "YOU WIN", color);
        rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
        rect.y = HAUTEUR_FENETRE / 8 -20;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "Votre score : ", color);
        rect.x = (2*LARGEUR_FENETRE / 4) - (surfaceTexte->w / 2) - 70;
        rect.y = 2*HAUTEUR_FENETRE / 8 +10;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "* score *", color);
        rect.x = (3*LARGEUR_FENETRE / 4) - (surfaceTexte->w / 2) -45;
        rect.y = 2*HAUTEUR_FENETRE / 8 + 10;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        pseudoTTF = creerTexte (pseudoTTF, METHODE_RAPIDE, helvFont, "Veuillez entrer votre pseudo :", pseudoColor);
        pseudoRect.x = (LARGEUR_FENETRE / 2) - (pseudoTTF->w / 2);
        pseudoRect.y = (HAUTEUR_FENETRE) / 2 -20;
        SDL_BlitSurface (pseudoTTF, NULL, surface, &pseudoRect);
        SDL_FreeSurface (pseudoTTF);
        ValiderTTF = creerTexte (ValiderTTF, METHODE_RAPIDE, helvFont, "Valider", ValiderColor);
        ValiderRect.x = (LARGEUR_FENETRE / 2) - (ValiderTTF->w / 2);
        ValiderRect.y = (3 * HAUTEUR_FENETRE) / 4 +10;
        SDL_BlitSurface (ValiderTTF, NULL, surface, &ValiderRect);
        SDL_FreeSurface (ValiderTTF);
        SDL_UpdateWindowSurface (fenetre);

        if (passlen > 0)
        {
            surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, texte, color);
            rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
            rect.y = 5*HAUTEUR_FENETRE / 8 -20;
            SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
            SDL_FreeSurface (surfaceTexte);
            SDL_UpdateWindowSurface (fenetre);
        }
    }

    SDL_StopTextInput();
   
   
   if( *onoff == 1 ) Mix_HaltMusic(); else playmusic (*musique, gMusic);
   libererPolice (helvFont);
   libererPolice (pixFont);
   libererPolice (contfuFont);
   SDL_DestroyWindow (fenetre);
}

void loose (Mix_Chunk* gSound)
{
    SDL_Window* fenetre = NULL;
    SDL_Surface* surface = NULL;
    SDL_Surface* titreTTF = NULL;
    TTF_Font* pixFont = NULL;
    TTF_Font* helvFont = NULL;
    SDL_Rect titreRect;
    SDL_Color TitreColor = {0, 0, 0, 0};
    SDL_Surface* JouerTTF = NULL;
    SDL_Rect JouerRect;
    SDL_Color JouerColor = {0, 0, 0, 0};
    pixFont = chargerPolice (pixFont, PIXFONT, 110);
    helvFont = chargerPolice (helvFont, HELVFONT, 60);
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 255, 34, 34) );
    titreTTF = creerTexte (titreTTF, METHODE_BELLE, pixFont, "GAME OVER", TitreColor);
    titreRect.x = (LARGEUR_FENETRE / 2) - (titreTTF->w / 2);
    titreRect.y = HAUTEUR_FENETRE / 2 -80;
    SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
    SDL_FreeSurface (titreTTF);
    JouerTTF = creerTexte (JouerTTF, METHODE_RAPIDE, helvFont, "You lose the game !", JouerColor);
    JouerRect.x = (LARGEUR_FENETRE / 2) - (JouerTTF->w / 2);
    JouerRect.y = HAUTEUR_FENETRE / 2 + 30;
    SDL_BlitSurface (JouerTTF, NULL, surface, &JouerRect);
    SDL_FreeSurface (JouerTTF);
    SDL_UpdateWindowSurface (fenetre);
    if( Mix_PlayingMusic() != 0 ) Mix_PauseMusic();
    playsound (4, gSound);
    SDL_Delay(3200);
    if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
    libererPolice (helvFont);
    libererPolice (pixFont);
    SDL_DestroyWindow (fenetre);
}