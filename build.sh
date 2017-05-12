#!/bin/sh
rm -rf bin
mkdir bin

g++ -c src/main.cpp -o bin/main.o
g++ bin/main.o -o bin/duelgraph -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

./bin/duelgraph
