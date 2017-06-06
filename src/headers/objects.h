#include <SFML/Audio.hpp>

#include "models.h"
#include "interface.h"

class Stage: public DrawableObj {
public:
	sf::Music* music;
	Stage(char img[], int screenWidth, char m[]) : DrawableObj(img) {
		int ratio = screenWidth / (sprite->getTexture()->getSize().x);
		sprite->setScale(ratio, ratio);

		music = new sf::Music();
		music->openFromFile(m);
	}
	inline bool exist() {
		return true;
	}
	inline sf::FloatRect getBound() {
		return sprite->getGlobalBounds();
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
	Direction preUpdateDir;
	Direction dir; //implement direction drawings on drawableobj level?

public:
	inline float getHp() {return stats.hp;}
	inline float getMaxHp() {return stats.maxHp;}
	inline float getMp() {return stats.mp;}
	inline float getMaxMp() {return stats.maxMp;}
	inline Direction getDirection() {return preUpdateDir;}

	Persona(char img[], int posX, int posY, Stats s);
	sf::FloatRect getBound();
	void update(sf::FloatRect fieldBounds);
	void collide(ModeledObj &collided);
	void run(Direction d);
	void stop();
	void turnBack();
	void teleport();
	bool exist();
	float getCollisionDmg();
	float getWeight();
};

class Bullet : public GameObj, public DrawableObj, public ModeledObj {
private:
	Ability w;
	Direction d;

	bool exploding;
	int explTime;
	float explScale;
	sf::Texture explTexture;
public:
	inline Direction getDirection() {return d;}
	inline void setExplScale(float scale) {explScale = scale; }

	Bullet(char img[], char explImg[], int posX, int posY, Direction dir, Ability a);
	void setSpriteScale(float scaleFactor);
	void update(sf::FloatRect fieldBounds);
	void collide(ModeledObj &collided);
	sf::FloatRect getBound();
	bool exist();
	float getCollisionDmg();
	float getWeight();
};