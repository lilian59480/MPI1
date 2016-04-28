#include "password.h"

int password() {
    SDL_Window* fenetrepass = NULL;
    char texte[PASSMAX] = {0};
    size_t passlen = 0, l;
    SDL_bool done = SDL_FALSE;
    SDL_Rect rect; 
    SDL_Event ev; 
    
    SDL_Surface* ValiderTTF = NULL;
    SDL_Rect ValiderRect;
    SDL_Color ValiderColor = {0, 0, 0, 0};
    int ValiderTTFW = 0;
    int ValiderTTFH = 0;
    
    TTF_Font* eraserFont = NULL;
    SDL_Surface* surface = NULL;
    eraserFont = chargerPolice (eraserFont, ERASERFONT, 25);
    SDL_Surface* surfaceTexte = NULL;
     SDL_Color color = {0, 0, 0, 0};
   
    
    fenetrepass = SDL_CreateWindow ("MPI1 Puzzle Password", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETREPASS, HAUTEUR_FENETREPASS, SDL_WINDOW_SHOWN);

    surface = SDL_GetWindowSurface (fenetrepass);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, eraserFont, "Mot de passe", color);
    rect.x = (LARGEUR_FENETREPASS / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETREPASS / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte); 
    ValiderTTF = creerTexte (ValiderTTF, METHODE_RAPIDE, eraserFont, "Valider", ValiderColor);
    ValiderRect.x = 10;
    ValiderRect.y = (3*HAUTEUR_FENETREPASS) / 4;
    SDL_BlitSurface (ValiderTTF, NULL, surface, &ValiderRect);
    SDL_FreeSurface (ValiderTTF);
              
    SDL_UpdateWindowSurface (fenetrepass);  
    
    SDL_StartTextInput();
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
                if(ev.key.keysym.sym == SDLK_BACKSPACE && passlen > 0)
                {
                    texte[passlen - 1] = 0;
                    passlen--;
                    puts(texte); 
                }
                else if (ev.key.keysym.sym == SDLK_ESCAPE)
                {
				    done = SDL_TRUE;                    
                }
                break;
            case SDL_TEXTINPUT : 
                l = strlen(ev.text.text);
                strncpy(texte + passlen, ev.text.text, PASSMAX - 1 - passlen);
                passlen += l;
                if(passlen > PASSMAX - 1)
                {
                    passlen = PASSMAX - 1;
                }
                puts(texte); 
                break;
        }  
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, eraserFont, "Mot de passe", color);
    rect.x = (LARGEUR_FENETREPASS / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETREPASS / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);        
    ValiderTTF = creerTexte (ValiderTTF, METHODE_RAPIDE, eraserFont, "Valider", ValiderColor);
    ValiderRect.x = 10;
    ValiderRect.y = (3*HAUTEUR_FENETREPASS) / 4;
    SDL_BlitSurface (ValiderTTF, NULL, surface, &ValiderRect);
    SDL_FreeSurface (ValiderTTF); 
    SDL_UpdateWindowSurface (fenetrepass);
    if (passlen>0)
    {
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, eraserFont, texte, color);
    rect.x = (LARGEUR_FENETREPASS / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETREPASS / 2;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);        
    SDL_UpdateWindowSurface (fenetrepass);             
    }
    }
    SDL_StopTextInput();
   
    
    SDL_DestroyWindow(fenetrepass);
    return 0;
}


short clickPass (TTF_Font* Font, char* String, int TTFW, int TTFH, SDL_Event event, SDL_Rect Rect)
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