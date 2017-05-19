#include <SFML/Audio.hpp>

#include "models.h"
#include "interface.h"

class Stage: public DrawableObj {
public:
	sf::Music music;
	inline Stage(char img[], char m[]) : DrawableObj(img) {
		music.openFromFile(m);
	}
	inline bool exist() {
		return true;
	}
};

class Persona: public GameObj, public DrawableObj, public ModeledObj {
private:
	float currentSpeed;
	bool running;
	bool bouncing;
	bool teleporting;
	Direction dir; //implement direction drawings on drawableobj level?

protected:
	Stats stats;

public:
	Persona(char img[], int posX, int posY, Stats s);
	sf::FloatRect getBound();
	void update();
	void collide(ModeledObj &collided);
	bool exist();
	float getCollisionDmg();
	float getWeight();
	void run(Direction d);
	void stop();
	void turnBack();
	void teleport();
};

class Bullet : public GameObj, public DrawableObj, public ModeledObj {
public:
	Bullet(char img[], int posX, int posY);
	sf::FloatRect getBound();
	void update();
	void collide(ModeledObj &collided);
	bool exist();
	float getCollisionDmg();
	float getWeight();
};