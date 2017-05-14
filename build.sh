#!/bin/sh
rm -rf bin
mkdir bin

g++ -c src/main.cpp -o bin/main.o
g++ -c src/Player.cpp -o bin/Player.o
g++ bin/main.o bin/Player.o -o bin/duelgraph -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

./bin/duelgraph
