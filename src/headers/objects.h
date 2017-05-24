#include <SFML/Audio.hpp>

#include "models.h"
#include "interface.h"

class Stage: public DrawableObj {
public:
	sf::Music* music;
	inline Stage(char img[], char m[]) : DrawableObj(img) {
		music = new sf::Music();
		music->openFromFile(m);
	}
	inline bool exist() {
		return true;
	}
	inline sf::FloatRect getBound() {
		return sprite->getLocalBounds();
	}
};

class Persona: public GameObj, public DrawableObj, public ModeledObj {
private:
	float currentSpeed;
	bool running;
	bool bouncing;
	bool teleporting;

protected:
	Stats stats;
	Direction dir; //implement direction drawings on drawableobj level?

public:
	Persona(char img[], int posX, int posY, Stats s);
	sf::FloatRect getBound();
	inline float getHp() {return stats.hp;}
	inline float getMaxHp() {return stats.maxHp;}
	inline float getMp() {return stats.mp;}
	inline float getMaxMp() {return stats.maxMp;}
	void update(sf::FloatRect fieldBounds);
	void collide(ModeledObj &collided);
	inline Direction getDirection() {return dir;}
	bool exist();
	float getCollisionDmg();
	float getWeight();
	void run(Direction d);
	void stop();
	void turnBack();
	void teleport();
};

class Bullet : public GameObj, public DrawableObj, public ModeledObj {
private:
	Ability w;
	Direction d;

	bool exploding;
	int explTime;
	sf::Texture explTexture;
public:
	Bullet(char img[], char explImg[], int posX, int posY, Direction dir, Ability a);
	void setSpriteScale(float scaleFactor);
	sf::FloatRect getBound();
	void update(sf::FloatRect fieldBounds);
	void collide(ModeledObj &collided);
	inline Direction getDirection() {return d;}
	bool exist();
	float getCollisionDmg();
	float getWeight();
};