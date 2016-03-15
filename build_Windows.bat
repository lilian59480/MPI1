title Compilation
mkdir Output
copy dll\ Output\
gcc -Wall -Wextra -ggdb -Og -L./lib -I./include src/main.c -o ./Output/MPI.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
pause