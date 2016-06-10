# MPI 2016 Arcade 2i Puzzle

**Avec des mots de passe**

Arcade 2i est un projet réalisé dans le cadre des études en première année de la formation IG2I de Centrale Lille

## Commencer

### Prérequis

Pour Windows :

- [MinGW avec MySYS](http://www.mingw.org/)
- [Git (Optionel)](https://git-scm.com/)

Pour GNU/Linux :
Les exemples ici sont pour les systèmes basés sur GNU/Debian

- GCC `# apt-get install gcc`
- Make `# apt-get install make`
- Git (Optionel) `# apt-get install git`
- Astyle (Optionel) `# apt-get install astyle`

### Compiler

Pour Windows :

- Installer les prérequis
- Rajouter MinGW et MySYS dans le Path
- Télécharger le zip ou cloner ce repo
- Lancer un invité de commande ou PowerShell
- Executer `>make -B` ou `>sh build_All.sh` lors de la première compilation

Pour GNU/Linux :
Les exemples ici sont pour les systèmes basés sur GNU/Debian

- Installer les prérequis
- Télécharger le zip ou cloner ce repo
- Déplacer vous dans le répertoire avec un terminal
- Executer `$ make -B` ou `$ sh build_All.sh` lors de la première compilation

Le Makefile est tel qu'il supporte les 2 environements:

``` make
ifeq ($(OS),Windows_NT)
    GCC=gcc -Wall -Wextra -ggdb -Og -g -L./lib -I./include
    PARAM= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
    OUTPUT= ./Output/MPI.exe
else
    GCC=gcc -Wall -Wextra -ggdb -Og -g
    PARAM= -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
    OUTPUT= ./Output/MPI
endif

all: outputclean copy puzzle

copy:
    mkdir Output
    cp -R ./dll/* ./Output/

puzzle: common.o best.o option.o password.o jeu.o menu.o
    $(GCC) common.o best.o option.o password.o jeu.o menu.o src/main.c -o $(OUTPUT) $(PARAM)

common.o:
    $(GCC) -c src/common.c $(PARAM)

best.o:
    $(GCC) -c src/best.c $(PARAM)

option.o:
    $(GCC) -c src/option.c $(PARAM)

password.o:
    $(GCC) -c src/password.c $(PARAM)

menu.o:
    $(GCC) -c src/menu.c $(PARAM)

jeu.o:
    $(GCC) -c src/jeu.c $(PARAM)

outputclean:
    rm -Rf ./Output/

clean: outputclean
    rm -f *.o

stylish:
    astyle -A1 -s4 -S -K -Y -f -p -d -xe -k1 -W1 -j -c -z2 -n ./src/*.c ./src/*.h
```

## Jouer

Executer Output\MPI.exe ou `cd Output/ && ./MPI` pour lancer le jeu.

Il supporte pour les interfaces en ligne de commandes les options définies dans cette fonction:

```c
void lireParamShell (int argc, char** argv)
{
    ...
        printf ("Liste des commandes disponibles:\n");
        printf ("--help\t: Affiche cette aide\n");
        printf ("--delete\t: Reset les scores\n");
    ...
}
```