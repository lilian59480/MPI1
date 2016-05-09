#include "option.h"

int option(short* musique, short* onoff ) {
    SDL_Window* fenetreoption = NULL;
    SDL_bool done = SDL_FALSE;
    SDL_Rect rect; 
    SDL_Event ev; 
    
    SDL_Color noir = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 0, 0};
    
    SDL_Surface* txtTTF = NULL;
    SDL_Rect txtRect;
    
    SDL_Surface* onTTF = NULL;
    SDL_Rect onRect;
    
    SDL_Surface* offTTF = NULL;
    SDL_Rect offRect;
    
    SDL_Surface* RetourTTF = NULL;
    SDL_Rect RetourRect;
    SDL_Color RetourColor = {0, 0, 0, 0};
    int RetourTTFW = 0;
    int RetourTTFH = 0;
    
    SDL_Surface* Mus1TTF = NULL;
    SDL_Rect Mus1Rect;
    
    SDL_Surface* Mus2TTF = NULL;
    SDL_Rect Mus2Rect;
    
    SDL_Surface* Mus3TTF = NULL;
    SDL_Rect Mus3Rect;
    
    SDL_Surface* Mus4TTF = NULL;
    SDL_Rect Mus4Rect;
    
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
    
    TTF_Font* eraserFont = NULL;
    SDL_Surface* surface = NULL;
    eraserFont = chargerPolice (eraserFont, ERASERFONT, 25);
    SDL_Surface* surfaceTexte = NULL;
    SDL_Color color = {0, 0, 0, 0};
    
    fenetreoption = creerFenetre (fenetreoption, "MPI1 Option", LARGEUR_FENETRE, HAUTEUR_FENETRE);

    
    while(!done) 
    {
        SDL_WaitEvent(&ev);
        
        
        switch(ev.type)
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
                if (clickMenu (eraserFont, "Retour", RetourTTFW, RetourTTFH, ev, RetourRect))
                {
				    done = SDL_TRUE;
                }
                
                break;
                
            case SDL_MOUSEMOTION:
                delColor.r = hoverMenu (eraserFont, "Suprimer les highscores", delTTFW, delTTFH, ev, delRect);
                RetourColor.r = hoverMenu (eraserFont, "Retour", RetourTTFW, RetourTTFH, ev, RetourRect);
                break;
        }  
        
    surface = SDL_GetWindowSurface (fenetreoption);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 252, 220, 18) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, eraserFont, "Options", color);
    rect.x = (LARGEUR_FENETRE / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETRE / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte); 
    RetourTTF = creerTexte (RetourTTF, METHODE_RAPIDE, eraserFont, "Retour", RetourColor);  
    RetourRect.x = (LARGEUR_FENETRE / 2) - (RetourTTF->w / 2);
    RetourRect.y = (7*HAUTEUR_FENETRE) / 8;
    SDL_BlitSurface (RetourTTF, NULL, surface, &RetourRect);
    SDL_FreeSurface (RetourTTF);
    Mus1TTF = creerTexte (Mus1TTF, METHODE_RAPIDE, eraserFont, "Epic",(*musique == 1)? rouge : noir);  
    Mus1Rect.x = (LARGEUR_FENETRE / 5) - (Mus1TTF->w / 2);
    Mus1Rect.y = (3*HAUTEUR_FENETRE) /8;
    SDL_BlitSurface (Mus1TTF, NULL, surface, &Mus1Rect);
    SDL_FreeSurface (Mus1TTF);
    Mus2TTF = creerTexte (Mus2TTF, METHODE_RAPIDE, eraserFont, "Jazz", (*musique == 2)? rouge : noir);  
    Mus2Rect.x = (2*LARGEUR_FENETRE / 5) - (Mus2TTF->w / 2);
    Mus2Rect.y = (3*HAUTEUR_FENETRE) /8;
    SDL_BlitSurface (Mus2TTF, NULL, surface, &Mus2Rect);
    SDL_FreeSurface (Mus2TTF);
    Mus3TTF = creerTexte (Mus3TTF, METHODE_RAPIDE, eraserFont, "Casu", (*musique == 3)? rouge : noir);  
    Mus3Rect.x = (3*LARGEUR_FENETRE / 5) - (Mus3TTF->w / 2);
    Mus3Rect.y = (3*HAUTEUR_FENETRE) /8;
    SDL_BlitSurface (Mus3TTF, NULL, surface, &Mus3Rect);
    SDL_FreeSurface (Mus3TTF);
    Mus4TTF = creerTexte (Mus4TTF, METHODE_RAPIDE, eraserFont, "Enervant", (*musique == 4)? rouge : noir);  
    Mus4Rect.x = (4*LARGEUR_FENETRE / 5) - (Mus4TTF->w / 2);
    Mus4Rect.y = (3*HAUTEUR_FENETRE) /8;
    SDL_BlitSurface (Mus4TTF, NULL, surface, &Mus4Rect);
    SDL_FreeSurface (Mus4TTF);
    delTTF = creerTexte (delTTF, METHODE_RAPIDE, eraserFont, "Suprimer les highscores", delColor);  
    delRect.x = (LARGEUR_FENETRE / 2) - (delTTF->w / 2);
    delRect.y = (HAUTEUR_FENETRE) /4;
    SDL_BlitSurface (delTTF, NULL, surface, &delRect);
    SDL_FreeSurface (delTTF);
    CreditsTTF = creerTexte (CreditsTTF, METHODE_RAPIDE, eraserFont, "Credits", CreditsColor);  
    CreditsRect.x = (LARGEUR_FENETRE / 2) - (CreditsTTF->w / 2);
    CreditsRect.y = (5*HAUTEUR_FENETRE) /8;
    SDL_BlitSurface (CreditsTTF, NULL, surface, &CreditsRect);
    SDL_FreeSurface (CreditsTTF);
    txtTTF = creerTexte (txtTTF, METHODE_RAPIDE, eraserFont, "Desactiver musique", noir);  
    txtRect.x = (LARGEUR_FENETRE / 3) - (txtTTF->w / 2);
    txtRect.y = (HAUTEUR_FENETRE) /2;
    SDL_BlitSurface (txtTTF, NULL, surface, &txtRect);
    SDL_FreeSurface (txtTTF);
    onTTF = creerTexte (onTTF, METHODE_RAPIDE, eraserFont, "Oui", (*onoff == 1)? rouge : noir);  
    onRect.x = (7*LARGEUR_FENETRE / 10) - (onTTF->w / 2);
    onRect.y = (HAUTEUR_FENETRE) /2;
    SDL_BlitSurface (onTTF, NULL, surface, &onRect);
    SDL_FreeSurface (onTTF);
    offTTF = creerTexte (offTTF, METHODE_RAPIDE, eraserFont, "Non", (*onoff == 0)? rouge : noir);  
    offRect.x = (8*LARGEUR_FENETRE / 10) - (offTTF->w / 2);
    offRect.y = (HAUTEUR_FENETRE) /2;
    SDL_BlitSurface (offTTF, NULL, surface, &offRect);
    SDL_FreeSurface (offTTF);
    
    SDL_UpdateWindowSurface (fenetreoption);
    }
    
    
    
    
    
    
    
    
    
    
    SDL_DestroyWindow(fenetreoption);
    return 0;
}