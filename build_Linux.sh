mkdir Output
cp -R ./dll/* ./Output/
gcc -Wall -Wextra -ggdb -Og src/main.c -o ./Output/MPI -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
