#include "password.h"

int password(Mix_Chunk *gSound, short* musique, Mix_Music *gMusic) {
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
    
    SDL_Surface* AnnulerTTF = NULL;
    SDL_Rect AnnulerRect;
    SDL_Color AnnulerColor = {0, 0, 0, 0};
    int AnnulerTTFW = 0;
    int AnnulerTTFH = 0;

    TTF_Font* contfuFont = NULL;
    TTF_Font* helvFont = NULL;
    SDL_Surface* surface = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 35);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 50);
    SDL_Surface* surfaceTexte = NULL;
    SDL_Color color2 = {255, 255, 255, 0};
    SDL_Color color = {0, 0, 0, 0};
   
    fenetrepass = creerFenetre (fenetrepass, TITREJEU, LARGEUR_FENETREPASS, HAUTEUR_FENETREPASS);
    
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
                else if (ev.key.keysym.sym == SDLK_RETURN)
                {
                    printf("testvalider\n");   
                    valider(texte, gSound, musique, gMusic);                 
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
            case SDL_MOUSEBUTTONDOWN:
                playsound(3,gSound);
                if (clickMenu (helvFont, "Valider", ValiderTTFW, ValiderTTFH, ev, ValiderRect) )
                {
                    printf("testvalider\n");
                    valider(texte, gSound, musique, gMusic);
                    ev.type = SDL_KEYDOWN;
                    ev.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&ev);
                }
                if (clickMenu (helvFont, "Annuler", AnnulerTTFW, AnnulerTTFH, ev, AnnulerRect) )
                {
                    done = SDL_TRUE;
                }
                
                break;
                
            case SDL_MOUSEMOTION:
                ValiderColor.r = hoverMenu (helvFont, "Valider", ValiderTTFW, ValiderTTFH, ev, ValiderRect);
                AnnulerColor.r = hoverMenu (helvFont, "Annuler", AnnulerTTFW, AnnulerTTFH, ev, AnnulerRect);
                break;
        }  
    surface = SDL_GetWindowSurface (fenetrepass);
    SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, contfuFont, "Mot de passe", color2);
    rect.x = (LARGEUR_FENETREPASS / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETREPASS / 8;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);        
    ValiderTTF = creerTexte (ValiderTTF, METHODE_RAPIDE, helvFont, "Valider", ValiderColor);
    ValiderRect.x = (LARGEUR_FENETREPASS / 4) - (ValiderTTF->w / 2);
    ValiderRect.y = (3*HAUTEUR_FENETREPASS) / 4;
    SDL_BlitSurface (ValiderTTF, NULL, surface, &ValiderRect);
    SDL_FreeSurface (ValiderTTF); 
    AnnulerTTF = creerTexte (AnnulerTTF, METHODE_RAPIDE, helvFont, "Annuler", AnnulerColor);
    AnnulerRect.x = (3*LARGEUR_FENETREPASS / 4) - (AnnulerTTF->w / 2);
    AnnulerRect.y = (3*HAUTEUR_FENETREPASS) / 4;
    SDL_BlitSurface (AnnulerTTF, NULL, surface, &AnnulerRect);
    SDL_FreeSurface (AnnulerTTF);
    SDL_UpdateWindowSurface (fenetrepass);
    if (passlen>0)
    {
    surfaceTexte = creerTexte (surfaceTexte, METHODE_BELLE, helvFont, texte, color);
    rect.x = (LARGEUR_FENETREPASS / 2) - (surfaceTexte->w / 2);
    rect.y = HAUTEUR_FENETREPASS / 2;
    SDL_BlitSurface (surfaceTexte, NULL, surface, &rect);
    SDL_FreeSurface (surfaceTexte);        
    SDL_UpdateWindowSurface (fenetrepass);             
    }
    }
    SDL_StopTextInput();

    libererPolice (helvFont);
    libererPolice (contfuFont);
    SDL_DestroyWindow(fenetrepass);
    return 0;
}

void valider(char *texte, Mix_Chunk *gSound, short* musique, Mix_Music *gMusic)
{
    if(strcmp(texte, "yolo") == 0)
    {
        printf("c est bien\n");
        playsound(1,gSound);
    }
    else if(strcmp(texte, "rick") == 0)
    {
        printf("c est bien\n");
        playsound(1,gSound);
        SDL_Delay(1500);
        *musique = 5;
        playmusic(*musique,gMusic);
        /* REMARQUE : Fermer la fenetre quand le mot de passe est bon? */
    }
    else
    {
        printf("c est nul\n");
        playsound(2,gSound);
    }
     
    return;
}