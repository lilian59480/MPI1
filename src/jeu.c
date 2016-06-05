#include "jeu.h"

Uint32 supprimerpoints (Uint32 intervalle, void* param)
{
    T_TempsScore* score = param;
    score->score -= 1;
    score->s += 1;

    if (score->s >= 60)
    {
        score->s = 0;
        score->m += 1;

        if (score->m >= 60)
        {
            score->m = 0;
            score->h += 1;
        }
    }

    return intervalle;
}

void fenetreJeu (char* cheminniveau, short difficulte, short r, short v, short b, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff, unsigned long scoreactuel, short mdp)
{
    SDL_Window* fenetre = NULL;
    SDL_Surface* surface = NULL;
    SDL_Surface* image = NULL;
    SDL_bool continuer = SDL_FALSE;
    T_Cases plateau;
    T_TempsScore tempsScore;
    tempsScore.s = 0;
    tempsScore.m = 0;
    tempsScore.h = 0;
    tempsScore.score = 0;
    float h = 0;
    int i = 0, j = 0, iselect = 0, jselect = 0;
    char chemin[100];
    char scorelitteral[100];
    char tempslitteral[100];
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
    SDL_TimerID timer;
    int tempsActuel = 0;
    int tempsPrecedent = 0;
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
    SDL_Surface* scoreTTF = NULL;
    SDL_Rect scoreRect;
    SDL_Color scoreColor = {0, 0, 0, 0};
    TTF_Font* helvFont = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 40);
    /*
     * Toutes les secondes, on appelle la fonction qui retire des points du au temps écoulé.
     */
    timer = SDL_AddTimer (1000, supprimerpoints, &tempsScore);
    tempsScore.score = scoreactuel;

    switch (difficulte)
    {
        case 0:
            plateau.taillexy = 4;
            taillecaseplateau = 100;
            tempsScore.score *= 1;
            break;

        case 1:
            plateau.taillexy = 8;
            taillecaseplateau = 50;
            tempsScore.score *= 30;
            break;

        case 3:
            plateau.taillexy = 10;
            taillecaseplateau = 40;
            tempsScore.score *= 150;
            break;

        default:
            SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur interne", "Difficulte inconnu" , NULL);
            exit (EXIT_FAILURE);
            break;
    }

    melangercase (&plateau);
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE * 2, 3 * HAUTEUR_FENETRE / 2);
    surface = SDL_GetWindowSurface (fenetre);
    verifierCouleur (&r, &v, &b);

    if (snprintf (chemin, 95, "%s%s0.png", IMAGEJEUDIRECTORY, cheminniveau) < 0)
    {
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur interne", "Chemin introuvable" , NULL);
        exit (EXIT_FAILURE);
    }

    image = chargerImage (image, chemin);
    hauteur = (HAUTEUR_FENETRE / 2) - (image->h / 2);

    while (!continuer)
    {
        while (SDL_PollEvent (&event) )
        {
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
                                            else
                                            {
                                                plateau.plateau[iselect][jselect] = plateau.plateau[i][j];
                                                plateau.plateau[i][j] = plateau.selectionne;
                                                plateau.selectionne = value;
                                            }
                                        }
                                    }
                                }

                                printf ("Depos d'une case: %d,%d\n", caseclicx, caseclicy);
                                printf ("-2 points\n");
                                tempsScore.score -= 2;
                                _debugT_Cases (&plateau);

                                if (validerCase (&plateau) && plateau.selectionne == -1)
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
        }

        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent < 20)
        {
            SDL_Delay (20 - (tempsActuel - tempsPrecedent) );
        }

        tempsPrecedent = SDL_GetTicks();

        if (mdp == 2)
        {
            if (h > 1)
            {
                h = 0.0;
            }

            h += 0.01;
            hslToRgb (h, 1, 0.5, &r, &v, &b);
            verifierCouleur (&r, &v, &b);
        }

        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, r, v, b) );

        if (mdp == 1)
        {
            coeurcoeur (surface);
        }

        rectImage.x = 2 * LARGEUR_FENETRE - image->w - 100;
        rectImage.y = hauteur;
        SDL_BlitSurface (image, NULL, surface, &rectImage);
        rect2.w = taillecaseplateau;
        rect2.h = taillecaseplateau;
        QuitterTTF = creerTexte (QuitterTTF, METHODE_RAPIDE, helvFont, "Abandonner", QuitterColor);
        QuitterRect.x = (6 * LARGEUR_FENETRE / 4) - (QuitterTTF->w / 2) + 20;
        QuitterRect.y = (4 * HAUTEUR_FENETRE) / 4 + 20;
        SDL_BlitSurface (QuitterTTF, NULL, surface, &QuitterRect);
        SDL_FreeSurface (QuitterTTF);
        snprintf (scorelitteral, 98, "Score : %lu", tempsScore.score);
        scoreTTF = creerTexte (scoreTTF, METHODE_RAPIDE, helvFont, scorelitteral , scoreColor);
        scoreRect.x = 100;
        scoreRect.y = (4 * HAUTEUR_FENETRE) / 4 + 20;
        SDL_BlitSurface (scoreTTF, NULL, surface, &scoreRect);
        SDL_FreeSurface (scoreTTF);
        snprintf (tempslitteral, 98, "Temps : %02d : %02d : %02d", tempsScore.h, tempsScore.m, tempsScore.s);
        tempsTTF = creerTexte (tempsTTF, METHODE_RAPIDE, helvFont, tempslitteral, tempsColor);
        tempsRect.x = 100;
        tempsRect.y = (4 * HAUTEUR_FENETRE) / 4 + 100;
        SDL_BlitSurface (tempsTTF, NULL, surface, &tempsRect);
        SDL_FreeSurface (tempsTTF);
        cheatTTF = creerTexte (cheatTTF, METHODE_RAPIDE, helvFont, "cheat", cheatColor);
        cheatRect.x = (6 * LARGEUR_FENETRE / 4) - (cheatTTF->w / 2) + 20;
        cheatRect.y = (4 * HAUTEUR_FENETRE) / 4 + 50;
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

        drawGrille (surface, 100, hauteur, taillecaseplateau, plateau.taillexy );
        SDL_UpdateWindowSurface (fenetre);
    }

    SDL_RemoveTimer (timer);
    libererPolice (helvFont);
    SDL_DestroyWindow (fenetre);
    fenetre = NULL;

    if (win == 1)
    {
        printf ("C'est gagne\n");
        SDL_Delay (50);
        printf ("+2 points car depot case valide\n");
        tempsScore.score += 2;
        wine (gSound, gMusic, musique, onoff, tempsScore.score);
    }
    else if (win == 0)
    {
        printf ("C'est perdu\n");
        loose (gSound);
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
        SDL_ShowSimpleMessageBox (SDL_MESSAGEBOX_ERROR, "Erreur interne", "n est trop grand" , NULL);
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


/*         POUR LES COEURS       http://anomaly.developpez.com/tutoriel/sdl/partie2/   */

void setPixel (SDL_Surface* surf, int x, int y, Uint32 coul)
{
    * ( (Uint32*) (surf->pixels) + x + y * surf->w) = coul;
}

void setPixelVerif (SDL_Surface* surf, int x, int y, Uint32 coul)
{
    if (x >= 0 && x < surf->w &&
            y >= 0 && y < surf->h)
    {
        setPixel (surf, x, y, coul);
    }
}


void echangerEntiers (int* x, int* y)
{
    int t = *x;
    *x = *y;
    *y = t;
}

void ligne (SDL_Surface* surf, int x1, int y1, int x2, int y2, Uint32 coul)
{
    int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

    if (abs (x2 - x1) < abs (y2 - y1) )
    {
        /* parcours par l'axe vertical */
        if (y1 > y2)
        {
            echangerEntiers (&x1, &x2);
            echangerEntiers (&y1, &y2);
        }

        xincr = x2 > x1 ? 1 : -1;
        dy = y2 - y1;
        dx = abs (x2 - x1);
        d = 2 * dx - dy;
        aincr = 2 * (dx - dy);
        bincr = 2 * dx;
        x = x1;
        y = y1;
        setPixelVerif (surf, x, y, coul);

        for (y = y1 + 1; y <= y2; ++y)
        {
            if (d >= 0)
            {
                x += xincr;
                d += aincr;
            }
            else
            {
                d += bincr;
            }

            setPixelVerif (surf, x, y, coul);
        }
    }
    else
    {
        /* parcours par l'axe horizontal */
        if (x1 > x2)
        {
            echangerEntiers (&x1, &x2);
            echangerEntiers (&y1, &y2);
        }

        yincr = y2 > y1 ? 1 : -1;
        dx = x2 - x1;
        dy = abs (y2 - y1);
        d = 2 * dy - dx;
        aincr = 2 * (dy - dx);
        bincr = 2 * dy;
        x = x1;
        y = y1;
        setPixelVerif (surf, x, y, coul);

        for (x = x1 + 1; x <= x2; ++x)
        {
            if (d >= 0)
            {
                y += yincr;
                d += aincr;
            }
            else
            {
                d += bincr;
            }

            setPixelVerif (surf, x, y, coul);
        }
    }
}

void ligneHorizontale (SDL_Surface* surf, int x, int y, int w, Uint32 coul)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = 1;
    SDL_FillRect (surf, &r, coul);
}

void ligneVerticale (SDL_Surface* surf, int x, int y, int h, Uint32 coul)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 1;
    r.h = h;
    SDL_FillRect (surf, &r, coul);
}


void disque (SDL_Surface* surf, int cx, int cy, int rayon, int coul)
{
    int d, y, x;
    d = 3 - (2 * rayon);
    x = 0;
    y = rayon;

    while (y >= x)
    {
        ligneHorizontale (surf, cx - x, cy - y, 2 * x + 1, coul);
        ligneHorizontale (surf, cx - x, cy + y, 2 * x + 1, coul);
        ligneHorizontale (surf, cx - y, cy - x, 2 * y + 1, coul);
        ligneHorizontale (surf, cx - y, cy + x, 2 * y + 1, coul);

        if (d < 0)
        {
            d = d + (4 * x) + 6;
        }
        else
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }

        x++;
    }
}

void heart (SDL_Surface* surface, short x, short y)
{
    disque (surface , x, y, 50, SDL_MapRGB (surface->format, 255, 0, 0) );
    disque (surface , x + 100, y, 50, SDL_MapRGB (surface->format, 255, 0, 0) );
    disque (surface , x + 50, y + 50, 45, SDL_MapRGB (surface->format, 255, 0, 0) );
    short xc = x - 40, xc2 = x + 50, yc = y + 30, yc2 = y + 150;

    for (xc = x - 40; xc <= xc2; xc++)
    {
        ligne (surface, xc, yc, xc2, yc2, SDL_MapRGB (surface->format, 255, 0, 0) );
        yc2--;
    }

    xc = x + 140;
    yc2 = y + 150;

    for (xc = x + 140; xc >= xc2; xc--)
    {
        ligne (surface, xc, yc, xc2, yc2, SDL_MapRGB (surface->format, 255, 0, 0) );
        yc2--;
    }
}


void coeurcoeur (SDL_Surface* surface)
{
    short i, j;

    for (i = 0; i <= (3 * HAUTEUR_FENETRE / 2); i = i + 200)
    {
        for (j = 0; j <= (LARGEUR_FENETRE * 2); j = j + 200)
        {
            heart (surface, j, i);
        }
    }
}









/*                       ECRAN FIN                 */

void wine (Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff, unsigned long scorefinal)
{
    SDL_Window* fenetre = NULL;
    SDL_Surface* surface = NULL;
    char texte[PSEUDOMAX] = {0};
    char scorelitteral[100];
    snprintf (scorelitteral, 98, "Votre score : %lu", scorefinal);
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
                    ajouterScore (scorefinal, texte);
                    done = SDL_TRUE;
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
                    ajouterScore (scorefinal, texte);
                    done = SDL_TRUE;
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
        rect.y = HAUTEUR_FENETRE / 8 - 20;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, scorelitteral, color);
        rect.x = (2 * LARGEUR_FENETRE / 4) - (surfaceTexte->w / 2) - 70;
        rect.y = 2 * HAUTEUR_FENETRE / 8 + 10;
        SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
        SDL_FreeSurface (surfaceTexte);
        pseudoTTF = creerTexte (pseudoTTF, METHODE_RAPIDE, helvFont, "Veuillez entrer votre pseudo :", pseudoColor);
        pseudoRect.x = (LARGEUR_FENETRE / 2) - (pseudoTTF->w / 2);
        pseudoRect.y = (HAUTEUR_FENETRE) / 2 - 20;
        SDL_BlitSurface (pseudoTTF, NULL, surface, &pseudoRect);
        SDL_FreeSurface (pseudoTTF);
        ValiderTTF = creerTexte (ValiderTTF, METHODE_RAPIDE, helvFont, "Valider", ValiderColor);
        ValiderRect.x = (LARGEUR_FENETRE / 2) - (ValiderTTF->w / 2);
        ValiderRect.y = (3 * HAUTEUR_FENETRE) / 4 + 10;
        SDL_BlitSurface (ValiderTTF, NULL, surface, &ValiderRect);
        SDL_FreeSurface (ValiderTTF);
        SDL_UpdateWindowSurface (fenetre);

        if (passlen > 0)
        {
            surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, texte, color);
            rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
            rect.y = 5 * HAUTEUR_FENETRE / 8 - 20;
            SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
            SDL_FreeSurface (surfaceTexte);
            SDL_UpdateWindowSurface (fenetre);
        }
    }

    SDL_StopTextInput();

    if ( *onoff == 1 )
    {
        Mix_HaltMusic();
    }
    else
    {
        playmusic (*musique, gMusic);
    }

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
    titreRect.y = HAUTEUR_FENETRE / 2 - 80;
    SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
    SDL_FreeSurface (titreTTF);
    JouerTTF = creerTexte (JouerTTF, METHODE_RAPIDE, helvFont, "You lose the game !", JouerColor);
    JouerRect.x = (LARGEUR_FENETRE / 2) - (JouerTTF->w / 2);
    JouerRect.y = HAUTEUR_FENETRE / 2 + 30;
    SDL_BlitSurface (JouerTTF, NULL, surface, &JouerRect);
    SDL_FreeSurface (JouerTTF);
    SDL_UpdateWindowSurface (fenetre);

    if ( Mix_PlayingMusic() != 0 )
    {
        Mix_PauseMusic();
    }

    playsound (4, gSound);
    SDL_Delay (3200);

    if ( Mix_PausedMusic() == 1 )
    {
        Mix_ResumeMusic();
    }

    libererPolice (helvFont);
    libererPolice (pixFont);
    SDL_DestroyWindow (fenetre);
}


float hue2rgb (float p, float q, float t)
{
    if (t < 0)
    {
        t += 1;
    }

    if (t > 1)
    {
        t -= 1;
    }

    if (t < 0.16666667)
    {
        return p + (q - p) * 6 * t;
    }

    if (t < 0.5)
    {
        return q;
    }

    if (t < 0.66666667)
    {
        return p + (q - p) * (0.66666667 - t) * 6;
    }

    return p;
}


void hslToRgb (float h, float s, float l, short* r, short* g, short* b)
{
    float q, p;

    if (s == 0)
    {
        * (r) = * (g) = * (b) = l;
    }
    else
    {
        q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        p = 2 * l - q;
        * (r) = round (hue2rgb (p, q, h + 0.16666667) * 255.0);
        * (g) = round (hue2rgb (p, q, h) * 255.0);
        * (b) = round (hue2rgb (p, q, h - 0.16666667) * 255.0);
    }
}