#include <SFML/Graphics.hpp>

using namespace sf;

typedef enum {
	N,
	S,
	E,
	W
} Direction;

class GameObj {
private: 
	bool exist;

public:
	inline GameObj() {
		exist = true;
	}
	inline bool doesExists() {return exist;}
	inline void removeFromGame() {exist = false;}
};

class DrawableObj : public GameObj {
protected:
	Sprite *sprite;
	Texture texture;

public:
	inline DrawableObj(char img[]) : GameObj() {
		texture.loadFromFile(img);
		texture.setSmooth(true);
		sprite = new Sprite(texture);
	}

	inline void draw(RenderWindow &window) {
		window.draw(*sprite);
	}

	inline FloatRect getBound() {return sprite->getGlobalBounds();}
};

class ModeledObj : public DrawableObj {
public:
	inline ModeledObj(char img[]) : DrawableObj(img) {}
	virtual void update(FloatRect fieldBounds) = 0;
	virtual void collide(ModeledObj &collided) = 0;
	virtual Direction getDirection() = 0;
	virtual float getCollisionDmg() = 0;
	virtual float getWeight() = 0;
};

