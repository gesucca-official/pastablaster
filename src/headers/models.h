#include <SFML/Graphics.hpp>

typedef enum {
	N,
	S,
	E,
	W
} Direction;

class GameObj {
public:
	inline GameObj() {
		exist = true;
	}
	bool exist;
};

class DrawableObj {
protected:
	sf::Sprite *sprite;
	sf::Texture texture;
	
public:
	inline DrawableObj(char img[]) {
		texture.loadFromFile(img);
		texture.setSmooth(true);
		sprite = new sf::Sprite(texture);
	} 
	inline void draw(sf::RenderWindow &window) {
		window.draw(*sprite);
	}
	virtual bool exist() = 0;
	virtual sf::FloatRect getBound() = 0;
};

class ModeledObj {
public:
	virtual void update(sf::FloatRect fieldBounds) = 0;
	virtual void collide(ModeledObj &collided) = 0;
	virtual Direction getDirection() = 0;
	virtual bool exist() = 0;
	virtual sf::FloatRect getBound() = 0;
	virtual float getCollisionDmg() = 0;
	virtual float getWeight() = 0;
};

