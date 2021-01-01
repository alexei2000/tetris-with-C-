g++ -c main.cpp -I/SFML-2.5.1/include
g++ main.o -o build/tetris -L/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system