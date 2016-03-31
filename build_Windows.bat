title Compilation
mkdir Output
robocopy dll\ Output\ /E
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include src/main.c -o ./Output/MPI.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
pause