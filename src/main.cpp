#include <SFML/Audio.hpp>

#include <string.h>

#include "headers/engine.h"

using namespace sf;
using std::vector;

FloatRect fieldBounds;
vector<DrawableObj*> toBeDrawn;
vector<ModeledObj*> toBeUpd;
vector<ModeledObj*> playerSide;
vector<ModeledObj*> oppoSide;

int main() {

	/*CREATE WINDOW*/
	sf::VideoMode vm = sf::VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// view needs to be same pixels of background!!
	// 'til I find a better way to do it, obviously
	View view(FloatRect(0, 0, 1366, 768));
	window.setView(view);

	// stage
	char stagePath[] = "./img/bkg.png";
	char musicPath[] =  "./sng/song.ogg";

	Stage stage(stagePath, musicPath);
	stage.music.setLoop(true);
	stage.music.play();
	toBeDrawn.push_back(&stage);

	fieldBounds = stage.getBound();

	// big mario
	char marioPath[] = "./img/player.png";
	ControlSet marioControls;
	marioControls.goRight = Keyboard::D;
	marioControls.goLeft = Keyboard::A;
	marioControls.goUp = Keyboard::W;
	marioControls.goDown = Keyboard::S;
	marioControls.teleport = Keyboard::Space;
	marioControls.ability1 = Keyboard::M;
	marioControls.ability2 = Keyboard::N;

	Stats s;
	s.hp = 100.0;
	s.mp = 100;
	s.manaRegen = 0.5f;
	s.weigth = 2.0;
	s.collisionDmg = 25.0;
	s.maxSpeed=8.0;
	s.accel= 1.0;
	s.decel = 1.0;
	s.teleportDist=100.0;

	Ability n;
	n.dmg=30,0;
	n.bulletWeight = 20;
	n.bulletSpeed= 5;
	n.shootSpeed=20;
	n.manaCost=10;
	strcpy( n.bulletImg, "./img/Mario_Nintendo.png" );

	AbilitySet as;
	as.a1 = n;
	as.a2 = n;

	Player mario(marioPath, s, marioControls, as);
	toBeDrawn.push_back(&mario);
	toBeUpd.push_back(&mario);
	playerSide.push_back(&mario);

	// a bad guy to test collisions
	char oppoPath[] = "./img/oppo.png";
	Persona badguy(oppoPath, 500, 200, s);
	toBeDrawn.push_back(&badguy);
	toBeUpd.push_back(&badguy);
	oppoSide.push_back(&badguy);

	//LIFEBAR
	sf::RectangleShape playerLifeBar(sf::Vector2f(200, 40));
	playerLifeBar.setPosition(20, 15);
	playerLifeBar.setFillColor(sf::Color::Cyan);

	// Start the game loop
	while (window.isOpen()) {

		 // Process events
		Event event;
		while (window.pollEvent(event)) {

			mario.handleControls(event, toBeDrawn, toBeUpd, playerSide);

			// ESC BUTTON: exit
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();
			}
		}



		window.clear();

		garbageCollection(toBeDrawn, toBeUpd, playerSide, oppoSide);

		//update and draw
		for (int i=0; i<toBeUpd.size(); i++)
			toBeUpd[i]->update(fieldBounds);
		for (int i=0; i<toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		detectCollisions(playerSide, oppoSide);

		//out of the vectors? is a good idea?
		window.draw(playerLifeBar);

		window.display();
	}

	return EXIT_SUCCESS;
}