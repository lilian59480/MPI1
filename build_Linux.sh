mkdir Output
cp -R ./dll/* ./Output/
gcc -Wall -Wextra -ggdb -Og src/common.c -c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og src/best.c -c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og src/menu.c -c -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og common.o best.o menu.o src/main.c -o ./Output/MPI -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
