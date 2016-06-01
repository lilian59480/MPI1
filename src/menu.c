#include "menu.h"

void fenetreChoixNiveau (SDL_Window* fenetre, T_MScore* score, Mix_Chunk* gSound, Mix_Music* gMusic, short* musique, short* onoff)
{
    /* On n'ouvre pas de nouvelle fenetre, on remplace la fenetre affiché (Pour une belle IHM) */
    short continuer = 1;
    SDL_Surface* surface = NULL;
    SDL_Event event;
    TTF_Font* contfuFont = NULL;
    TTF_Font* helvFont = NULL;
    helvFont = chargerPolice (helvFont, HELVFONT, 35);
    contfuFont = chargerPolice (contfuFont, CONTFUFONT, 60);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_Surface* titreTTF = NULL;
    SDL_Rect titreRect;
    SDL_Color TitreColor = {255, 255, 255, 0};
    SDL_Color noir = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 0, 0};
    SDL_Surface* ChatTTF = NULL;
    SDL_Rect ChatRect;
    SDL_Color ChatColor = {0, 0, 0, 0};
    int ChatTTFW = 0;
    int ChatTTFH = 0;
    SDL_Surface* ChienTTF = NULL;
    SDL_Rect ChienRect;
    SDL_Color ChienColor = {0, 0, 0, 0};
    int ChienTTFW = 0;
    int ChienTTFH = 0;
    SDL_Surface* PaysageTTF = NULL;
    SDL_Rect PaysageRect;
    SDL_Color PaysageColor = {0, 0, 0, 0};
    int PaysageTTFW = 0;
    int PaysageTTFH = 0;
    SDL_Surface* IG2ITTF = NULL;
    SDL_Rect IG2IRect;
    SDL_Color IG2IColor = {0, 0, 0, 0};
    int IG2ITTFW = 0;
    int IG2ITTFH = 0;
    SDL_Surface* RetourTTF = NULL;
    SDL_Rect RetourRect;
    SDL_Color RetourColor = {0, 0, 0, 0};
    int RetourTTFW = 0;
    int RetourTTFH = 0;
    
    SDL_Surface* easyTTF = NULL;
    SDL_Rect easyRect;
    int easyTTFW = 0;
    int easyTTFH = 0;
    SDL_Surface* moyTTF = NULL;
    SDL_Rect moyRect;
    int moyTTFW = 0;
    int moyTTFH = 0;
    SDL_Surface* durTTF = NULL;
    SDL_Rect durRect;
    int durTTFW = 0;
    int durTTFH = 0;
    
    short dificulte = 0;
    
    event.type = SDL_KEYDOWN;
    event.key.keysym.sym = SDLK_1;
    SDL_PushEvent (&event);

    while (continuer)
    {
        SDL_WaitEvent (&event);

        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                playsound (3, gSound);

                if (clickMenu (helvFont, "Chat", ChatTTFW, ChatTTFH, event, ChatRect) )
                {
                    fenetreJeu (score, "Chat/", dificulte, 255, 0, 255, gSound, gMusic, musique, onoff);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                    return;
                }

                else if (clickMenu (helvFont, "Chien", ChienTTFW, ChienTTFH, event, ChienRect) )
                {
                    fenetreJeu (score, "Chien/", dificulte, 255, 0, 255, gSound, gMusic, musique, onoff);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                    return;
                }

                else if (clickMenu (helvFont, "Paysage", PaysageTTFW, PaysageTTFH, event, PaysageRect) )
                {
                    fenetreJeu (score, "Paysage/", dificulte, 255, 0, 255, gSound, gMusic, musique, onoff);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                    return;
                }

                else if (clickMenu (helvFont, "IG2I", IG2ITTFW, IG2ITTFH, event, IG2IRect) )
                {
                    fenetreJeu (score, "IG2I/", dificulte, 255, 0, 255, gSound, gMusic, musique, onoff);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                    return;
                }

                else if (clickMenu (helvFont, "Retour", RetourTTFW, RetourTTFH, event, RetourRect) )
                {
                    return;
                }
                else if (clickMenu (helvFont, "Facile", easyTTFW, easyTTFH, event, easyRect) && (dificulte != 0) )
                {
                    dificulte = 0;
                }
                else if (clickMenu (helvFont, "Moyen", moyTTFW, moyTTFH, event, moyRect) && (dificulte != 1) )
                {
                    dificulte = 1;
                }
                else if (clickMenu (helvFont, "Difficile", durTTFW, durTTFH, event, durRect) && (dificulte != 3) )
                {
                   dificulte = 3;
                }
                break;

            case SDL_QUIT:
                exit (EXIT_SUCCESS);
                break;
                
            case SDL_KEYDOWN :
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                   return;
                }
                break;

            case SDL_MOUSEMOTION:
                ChatColor.b = hoverMenu (helvFont, "Chat", ChatTTFW, ChatTTFH, event, ChatRect);
                ChienColor.b = hoverMenu (helvFont, "Chien", ChienTTFW, ChienTTFH, event, ChienRect);
                PaysageColor.b = hoverMenu (helvFont, "Paysage", PaysageTTFW, PaysageTTFH, event, PaysageRect);
                IG2IColor.b = hoverMenu (helvFont, "IG2I", IG2ITTFW, IG2ITTFH, event, IG2IRect);
                RetourColor.b = hoverMenu (helvFont, "Retour", RetourTTFW, RetourTTFH, event, RetourRect);
                break;

            default:
                break;
        }

        /* On met une couleur de font */
        SDL_FillRect (surface, NULL, SDL_MapRGB (surface->format, 204, 72, 63) );
        titreTTF = creerTexte (titreTTF, METHODE_BELLE, contfuFont, "Choix du niveau", TitreColor);
        titreRect.x = (LARGEUR_FENETRE / 2) - (titreTTF->w / 2);
        titreRect.y = HAUTEUR_FENETRE / 12;
        SDL_BlitSurface (titreTTF, NULL, surface, &titreRect);
        SDL_FreeSurface (titreTTF);
        easyTTF = creerTexte (easyTTF, METHODE_RAPIDE, helvFont, "Facile", (dificulte == 0) ? rouge : noir);
        easyRect = rangMenu (easyTTF, 2);
        easyRect.x = (LARGEUR_FENETRE / 4) - (easyTTF->w / 2);
        SDL_BlitSurface (easyTTF, NULL, surface, &easyRect);
        SDL_FreeSurface (easyTTF);
        moyTTF = creerTexte (moyTTF, METHODE_RAPIDE, helvFont, "Moyen", (dificulte == 1) ? rouge : noir);
        moyRect = rangMenu (moyTTF, 2);
        moyRect.x = (2*LARGEUR_FENETRE / 4) - (moyTTF->w / 2);
        SDL_BlitSurface (moyTTF, NULL, surface, &moyRect);
        SDL_FreeSurface (moyTTF);
        durTTF = creerTexte (durTTF, METHODE_RAPIDE, helvFont, "Difficile", (dificulte == 3) ? rouge : noir);
        durRect = rangMenu (durTTF, 2);
        durRect.x = (3*LARGEUR_FENETRE/4) - (durTTF->w / 2);
        SDL_BlitSurface (durTTF, NULL, surface, &durRect);
        SDL_FreeSurface (durTTF);
        ChatTTF = creerTexte (ChatTTF, METHODE_RAPIDE, helvFont, "Chat", ChatColor);
        ChatRect = rangMenu (ChatTTF, 3);
        SDL_BlitSurface (ChatTTF, NULL, surface, &ChatRect);
        SDL_FreeSurface (ChatTTF);
        ChienTTF = creerTexte (ChienTTF, METHODE_RAPIDE, helvFont, "Chien", ChienColor);
        ChienRect = rangMenu (ChienTTF, 4);
        SDL_BlitSurface (ChienTTF, NULL, surface, &ChienRect);
        SDL_FreeSurface (ChienTTF);
        PaysageTTF = creerTexte (PaysageTTF, METHODE_RAPIDE, helvFont, "Paysage", PaysageColor);
        PaysageRect = rangMenu (PaysageTTF, 5);
        SDL_BlitSurface (PaysageTTF, NULL, surface, &PaysageRect);
        SDL_FreeSurface (PaysageTTF);
        IG2ITTF = creerTexte (IG2ITTF, METHODE_RAPIDE, helvFont, "IG2I", IG2IColor);
        IG2IRect = rangMenu (IG2ITTF, 6);
        SDL_BlitSurface (IG2ITTF, NULL, surface, &IG2IRect);
        SDL_FreeSurface (IG2ITTF);
        RetourTTF = creerTexte (RetourTTF, METHODE_RAPIDE, helvFont, "Retour", RetourColor);
        RetourRect = rangMenu (RetourTTF, 7);
        SDL_BlitSurface (RetourTTF, NULL, surface, &RetourRect);
        SDL_FreeSurface (RetourTTF);
        SDL_UpdateWindowSurface (fenetre);
    }

    libererPolice (helvFont);
    libererPolice (contfuFont);
}