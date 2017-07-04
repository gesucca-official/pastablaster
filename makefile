bin/combat: bin/main.o bin/inits.o bin/engine.o bin/Player.o bin/Persona.o bin/Bullet.o bin/load.so
	g++ bin/main.o bin/inits.o bin/engine.o bin/Player.o bin/Persona.o bin/Bullet.o bin/load.so -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -o bin/combat

bin/main.o:
	g++ -c src/main/main.cpp -o bin/main.o

bin/inits.o:
	g++ -c src/main/inits.cpp -o bin/inits.o

bin/engine.o:
	g++ -c src/main/engine.cpp -o bin/engine.o

bin/Player.o:
	g++ -c src/main/Player.cpp -o bin/Player.o

bin/Persona.o:
	g++ -c src/main/Persona.cpp -o bin/Persona.o

bin/Bullet.o:
	g++ -c src/main/Bullet.cpp -o bin/Bullet.o

bin/load.so:
	g++ -c -fPIC src/loader/load.cpp -o bin/load.o
	g++ -shared bin/load.o -o bin/load.so