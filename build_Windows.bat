title Compilation
mkdir Output
robocopy dll\ Output\ /E
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include -c src/common.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include -c src/best.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include -c src/menu.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include common.o best.o menu.o src/main.c -o ./Output/MPI.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
pause
