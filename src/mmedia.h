#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "model.h"

#include <iostream>

using namespace sf;

class DrawableObj {
public:
	DrawableObj(Element e) {
		char path[25];
		e.getImg(path);
		std::cout << path;
		std::cout << "imhere";
		texture.loadFromFile(path);
		sprite = new Sprite(texture);
	} 
	void draw(RenderWindow &window) {
		window.draw(*sprite);
	}
private:
	Sprite *sprite;
	Texture texture;
};

class ListenableObj;