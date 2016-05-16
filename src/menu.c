#include "menu.h"

void fenetreChoixNiveau (SDL_Window* fenetre, T_MScore* score, Mix_Chunk *gSound)
{
    /* On n'ouvre pas de nouvelle fenetre, on remplace la fenetre affiché (Pour une belle IHM) */
    TTF_Font* eraserFont = NULL;
    short continuer = 1;
    SDL_Surface* surface = NULL;
    SDL_Event event;
    TTF_Font* contfuFont = NULL;
    TTF_Font* helvFont = NULL;
    eraserFont = chargerPolice (eraserFont, ERASERFONT, 25);
    helvFont = chargerPolice (helvFont, "font/helv.ttf", 35);
    contfuFont = chargerPolice (contfuFont, "font/CONTFU.ttf", 60);
    surface = SDL_GetWindowSurface (fenetre);
    SDL_Surface* titreTTF = NULL;
    SDL_Rect titreRect;
    SDL_Color TitreColor = {255, 255, 255, 0};
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

    while (continuer)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                playsound(3,gSound);
                if (clickMenu (helvFont, "Chat", ChatTTFW, ChatTTFH, event, ChatRect) )
                {
                    fenetreJeu(score,"Chat/",0);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Chien", ChienTTFW, ChienTTFH, event, ChienRect) )
                {
                    fenetreJeu(score,"Chien/",0);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Paysage", PaysageTTFW, PaysageTTFH, event, PaysageRect) )
                {
                    fenetreJeu(score,"Paysage/",0);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "IG2I", IG2ITTFW, IG2ITTFH, event, IG2IRect) )
                {
                    fenetreJeu(score,"IG2I/",0);
                    event.type = SDL_KEYDOWN;
                    event.key.keysym.sym = SDLK_1;
                    SDL_PushEvent (&event);
                }

                if (clickMenu (helvFont, "Retour", RetourTTFW, RetourTTFH, event, RetourRect) )
                {
                    return;
                }

                break;

            case SDL_QUIT:
                exit (EXIT_SUCCESS);
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
        SDL_WaitEvent (&event);
        ChatTTF = creerTexte (ChatTTF, METHODE_RAPIDE, helvFont, "Chat", ChatColor);
        ChatRect = rangMenu (ChatTTF, 2);
        SDL_BlitSurface (ChatTTF, NULL, surface, &ChatRect);
        SDL_FreeSurface (ChatTTF);
        ChienTTF = creerTexte (ChienTTF, METHODE_RAPIDE, helvFont, "Chien", ChienColor);
        ChienRect = rangMenu (ChienTTF, 3);
        SDL_BlitSurface (ChienTTF, NULL, surface, &ChienRect);
        SDL_FreeSurface (ChienTTF);
        PaysageTTF = creerTexte (PaysageTTF, METHODE_RAPIDE, helvFont, "Paysage", PaysageColor);
        PaysageRect = rangMenu (PaysageTTF, 4);
        SDL_BlitSurface (PaysageTTF, NULL, surface, &PaysageRect);
        SDL_FreeSurface (PaysageTTF);
        IG2ITTF = creerTexte (IG2ITTF, METHODE_RAPIDE, helvFont, "IG2I", IG2IColor);
        IG2IRect = rangMenu (IG2ITTF, 5);
        SDL_BlitSurface (IG2ITTF, NULL, surface, &IG2IRect);
        SDL_FreeSurface (IG2ITTF);
        RetourTTF = creerTexte (RetourTTF, METHODE_RAPIDE, helvFont, "Retour", RetourColor);
        RetourRect = rangMenu (RetourTTF, 7);
        SDL_BlitSurface (RetourTTF, NULL, surface, &RetourRect);
        SDL_FreeSurface (RetourTTF);
        SDL_UpdateWindowSurface (fenetre);
    }
}