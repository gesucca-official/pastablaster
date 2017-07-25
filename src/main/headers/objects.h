#include <SFML/Audio.hpp>

#include "models.h"
#include "interface.h"

using namespace sf;

class Stage : public DrawableObj {
public:
	Music* music;

	inline Stage(char img[], int screenWidth, char m[]) : DrawableObj(img) {
		int ratio = screenWidth / (sprite->getTexture()->getSize().x);
		sprite->setScale(ratio, ratio);

		music = new Music();
		music->openFromFile(m);
	}

	inline FloatRect getBound() {
		return sprite->getGlobalBounds();
	}
};

class Bar : public DrawableObj {
public: 
	inline Bar(char img[]) : DrawableObj(img) {}
	inline void setPos(float x, float y) {sprite->setPosition(x,y);}
};

class Persona : public ModeledObj {
private:
	float currentSpeed;
	bool running;
	bool bouncing;
	bool teleporting;

protected:
	Stats stats;
	Direction preUpdateDir;
	Direction dir;
	float cooldown;

public:
	inline float getHp() {return stats.hp;}
	inline float getMaxHp() {return stats.maxHp;}
	inline float getMp() {return stats.mp;}
	inline float getMaxMp() {return stats.maxMp;}
	inline Direction getDirection() {return preUpdateDir;}

	inline virtual float getCollisionDmg() {return stats.collisionDmg;}
	inline virtual float getWeight() {return stats.weigth;}

	Persona(char img[], int posX, int posY, Stats s);

	void update(FloatRect fieldBounds);
	void collide(ModeledObj &collided);
	void run(Direction d);
	void stop();
	void teleport();
};

class Bullet : public ModeledObj {
private:
	bool exploding;
	int explTime;
	float explScale;
	Ability w;
	Texture explTexture;
	SoundBuffer *sfxb;
	Sound *sfx;

protected:
	Direction d;

public:
	inline Direction getDirection() {return d;}
	inline void setExplScale(float scale) {explScale = scale;}
	inline virtual float getCollisionDmg() {return w.dmg;}
	inline virtual float getWeight() {return w.bulletWeight;}

	Bullet(char img[], char explImg[], char soundfx[], int posX, int posY, Direction dir, Ability a);

	void update(FloatRect fieldBounds);
	void collide(ModeledObj &collided);
};

class CrazyBullet : public Bullet {
private:
	int crazyness;
	int r, g, b;
	bool hueUp;

public:
	inline CrazyBullet(char img[], char explImg[], char soundfx[], int posX, int posY, Direction dir, Ability a, int c) : Bullet(img, explImg, soundfx, posX, posY, dir, a) {
		r = 255, g = 255, b = 255;
		hueUp = true;
		crazyness = c;
	}
	void update(FloatRect fieldBounds);
};