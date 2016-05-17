#include "jeu.h"

void fenetreJeu (T_MScore* score, char* cheminniveau, short difficulte){
    SDL_Window *fenetre = NULL ;
    T_Cases plateau;
    switch (difficulte) {
        case 0:
            plateau.taillexy = 3;
        break;
        
        case 1:
            plateau.taillexy = 6;
        break;
        
        case 3:
            plateau.taillexy = 10;
        break;
        
        default:
            fprintf (stderr, "Difficulte inconnue : %d\n",difficulte );
            exit(EXIT_FAILURE);
        break;
    }
    printf("%s%s%d/\n",IMAGEJEUDIRECTORY,cheminniveau,difficulte);
    melangercase(&plateau);
    fenetre = creerFenetre(fenetre, TITREJEU, LARGEUR_FENETRE, HAUTEUR_FENETRE);
    SDL_Delay(2500);
    
    SDL_DestroyWindow(fenetre);
    fenetre = NULL;
    return;
}

void melangercase (T_Cases *plateau ) {
    int i;
    T_Case a[TAILLEPLATEAUMAX*TAILLEPLATEAUMAX];
    int taille = plateau->taillexy;
    int n = taille*taille;
    if (n > (TAILLEPLATEAUMAX*TAILLEPLATEAUMAX))
        {
            fprintf (stderr, "N est trop grand! :\n %d>%d \n",n,TAILLEPLATEAUMAX );
            exit(EXIT_FAILURE);
        }
    for (i=0;i < n;i++) {
        a[i] = i;
    }
    srand(time(NULL));
    for (i=0;i < n-2;i++) {
        int j;
        j = rand() % (n-i);
        T_Case k;
        k = a[i];
        a[i] = a[i+j];
        a[i+j] = k;
    }
    
    int j=0;
    int k=0;
    
    for (i=0;i<(taille*taille) ;i++,k++) {
        if (k>=taille) {
            k=0;
            j++;
        }
        plateau->plateau[j][k] = a[i];
    }

    _debugT_Cases(plateau);
}

void _debugT_Cases(T_Cases* plateau) {
    int i;
    int j;
    for (i=0; i < plateau->taillexy; i++)
    {
        for (j=0; j < plateau->taillexy; j++)
    {
        printf("{%d,%d} = %d\n",i,j,plateau->plateau[i][j]);
    }
    }
}