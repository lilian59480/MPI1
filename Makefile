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
