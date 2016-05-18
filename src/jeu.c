#include "jeu.h"

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte, short r, short v, short b )
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
    int value;
    int positionsourisx = 0;
    int positionsourisy = 0;
    int caseclicx = 0;
    int caseclicy = 0;

    switch (difficulte)
    {
        case 0:
            plateau.taillexy = 4;
            break;

        case 1:
            plateau.taillexy = 6;
            break;

        case 3:
            plateau.taillexy = 10;
            break;

        default:
            fprintf (stderr, "Difficulte inconnue : %d\n", difficulte );
            exit (EXIT_FAILURE);
            break;
    }

    melangercase (&plateau);
    fenetre = creerFenetre (fenetre, TITREJEU, LARGEUR_FENETRE * 2, HAUTEUR_FENETRE * 2);
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
        rect2.w = 100;
        rect2.h = 100;

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
                    rect.x = 100 + (100 * (i) );
                    rect.y = hauteur + (100 * (j) );
                }

                rect2.x = 0 + (100 * (value / plateau.taillexy) );
                rect2.y = 0 + (100 * (value % plateau.taillexy) );
                SDL_BlitSurface (image, &rect2, surface, &rect);
            }
        }

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.x > 100 && event.button.x < (100 + (image->w) ) )
                {
                    if (event.button.y > hauteur && event.button.y < (hauteur + (image->h) ) )
                    {
                        caseclicx = (event.button.x - 100) / 100;
                        caseclicy = (event.button.y - hauteur) / 100;

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
                                printf("C'est gagne\n");
                            }
                        }
                    }
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
                break;

            default:
                break;
        }

        drawGrille (surface, 100, hauteur, 100, plateau.taillexy );
        SDL_UpdateWindowSurface (fenetre);
    }

    SDL_DestroyWindow (fenetre);
    fenetre = NULL;
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