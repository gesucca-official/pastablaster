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

class UpdatableObj {
public:
	virtual void update() = 0;
};