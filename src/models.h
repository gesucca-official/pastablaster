#include <SFML/Graphics.hpp>

class DrawableObj {
protected:
	sf::Sprite *sprite;
	sf::Texture texture;
	
public:
	inline DrawableObj(char img[]) {
		texture.loadFromFile(img);
		sprite = new sf::Sprite(texture);
	} 
	inline void draw(sf::RenderWindow &window) {
		window.draw(*sprite);
	}
};

class ModeledObj {
public:
	bool removedFromField; //to be garbage collected before next draw

	virtual void update() = 0;
	virtual void collide(ModeledObj &collided) = 0;
	virtual sf::FloatRect getBound() = 0;

};