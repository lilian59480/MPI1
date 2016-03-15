mkdir Output
cp ./dll/* ./Output/
gcc -Wall -Wextra -ggdb -Og src/main.c -o ./Output/MPI.exe -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf