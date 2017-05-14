#include <SFML/Graphics.hpp>

class DrawableObj {
protected:
	sf::Sprite *sprite;
private:
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