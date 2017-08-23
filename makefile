CC = g++ -O3

MAIN_HEADERS = src/main/headers/characters.h src/main/headers/interface.h src/main/headers/main.h src/main/headers/main_decl.h src/main/headers/models.h src/main/headers/objects.h 
MAIN_OBJECTS = bin/main.o bin/inits.o bin/engine.o bin/Player.o bin/Persona.o bin/Opponent.o bin/Bullet.o
LIBS = bin/load.so
SFML = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# launcher module
bin/pastablaster: bin/combat src/launcher/main.cpp
	$(CC) src/launcher/main.cpp $(SFML) -o bin/pastablaster

# main module
bin/combat: $(MAIN_OBJECTS) $(LIBS)
	$(CC) $(MAIN_OBJECTS) $(LIBS) $(SFML) -o bin/combat

bin/%.o : src/main/%.cpp $(MAIN_HEADERS)
	$(CC) -c $< -o $@ 

# loader module
bin/load.so: src/loader/load.cpp src/loader/load.h
	$(CC) -c -fPIC src/loader/load.cpp -o bin/load.o
	$(CC) -shared bin/load.o -o bin/load.so

final: bin/pastablaster
	rm bin/*.o