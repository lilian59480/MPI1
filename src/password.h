#ifndef H_PASS
#define H_PASS

#include "common.h"


#define LARGEUR_FENETREPASS 400
#define HAUTEUR_FENETREPASS 300
#define PASSMAX 10

int password(Mix_Chunk *gSound);
void valider(char* texte, Mix_Chunk *gSound);

#endif