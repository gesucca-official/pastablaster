#include <string.h>

#include "headers/engine.h"

using namespace sf;
using std::vector;

Stage* stage;
Player* player;
Persona* opponent;

Shape* playerLifeBar;
Shape* oppoLifeBar;

Shape* playerManaBar;

vector<DrawableObj*> toBeDrawn;
vector<ModeledObj*> toBeUpd;
vector<ModeledObj*> playerSide;
vector<ModeledObj*> oppoSide;

Stage* initStage() {
	char stagePath[] = "./img/bkg.png";
	char musicPath[] =  "./sng/song.ogg";

	Stage *stage = new Stage(stagePath, musicPath);

	stage->music->setLoop(true);
	stage->music->play();
	stage->music->setVolume(100);

	toBeDrawn.push_back(stage);

	return stage;
}

Player* initPlayer() {
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
	s.maxHp = 100.0;
	s.mp = 100;
	s.maxMp = 100.0;
	s.manaRegen = 0.18f;
	s.weigth = 2.0;
	s.collisionDmg = 25.0;
	s.maxSpeed=8.0;
	s.accel= 1.0;
	s.decel = 1.0;
	s.teleportDist=150.0;

	Ability n;
	n.dmg=30.0;
	n.bulletWeight = 20;
	n.bulletSpeed= 5;
	n.shootSpeed=20;
	n.manaCost=10;
	strcpy( n.bulletImg, "./img/Mario_Nintendo.png" );
	strcpy(n.bulletExplImg, "./img/starburst-explosion.png");
	n.explFrames = 30;

	AbilitySet as;
	as.a1 = n;
	as.a2 = n;

	player = new Player(marioPath, s, marioControls, as);
	toBeDrawn.push_back(player);
	toBeUpd.push_back(player);
	playerSide.push_back(player);

	return player;
}

Persona* initOpponent() {

	char oppoPath[] = "./img/oppo.png";

	Stats s;
	s.hp = 100.0;
	s.maxHp = 100.0;
	s.mp = 100;
	s.maxMp = 100.0;
	s.manaRegen = 0.5f;
	s.weigth = 2.0;
	s.collisionDmg = 25.0;
	s.maxSpeed=8.0;
	s.accel= 1.0;
	s.decel = 1.0;
	s.teleportDist=100.0;

	opponent = new Persona(oppoPath, 500, 200, s);
	toBeDrawn.push_back(opponent);
	toBeUpd.push_back(opponent);
	oppoSide.push_back(opponent);

	return opponent;
}

int main() {

	sf::VideoMode vm = sf::VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// view needs to be same pixels of background!!
	// 'til I find a better way to do it, obviously
	View view(FloatRect(0, 0, 1366, 768));
	window.setView(view);

	stage = initStage();
	player = initPlayer();
	opponent = initOpponent();

	//needs some embellishments
	playerLifeBar = new RectangleShape(sf::Vector2f(400, 30));
	playerLifeBar->setPosition(20, 15);
	playerLifeBar->setFillColor(sf::Color::Green);
	playerManaBar = new RectangleShape(sf::Vector2f(350, 25));
	playerManaBar->setPosition(20, 45);
	playerManaBar->setFillColor(sf::Color::Blue);

	oppoLifeBar = new RectangleShape(sf::Vector2f(450, 30));
	oppoLifeBar->setOrigin(450, 0);
	oppoLifeBar->setPosition(1346, 15);
	oppoLifeBar->setFillColor(sf::Color::Green);

	// Start the game loop
	while (window.isOpen()) {

		// life and mana display logic
		float pLifePercent = (float) player->getHp() / (float) player->getMaxHp();
		playerLifeBar->setScale(pLifePercent, 1.0);
		float pManaPercent = (float) player->getMp() / (float) player->getMaxMp();
		playerManaBar->setScale(pManaPercent, 1.0);
		float oLifePercent = (float) opponent->getHp() / (float) opponent->getMaxHp();
		oppoLifeBar->setScale(oLifePercent, 1.0);

		// Process events
		Event event;
		while (window.pollEvent(event)) {

			player->handleControls(event, toBeDrawn, toBeUpd, playerSide);

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
			toBeUpd[i]->update(stage->getBound());
		for (int i=0; i<toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		detectCollisions(playerSide, oppoSide);

		//draw non game objects here
		window.draw(*playerLifeBar);
		window.draw(*playerManaBar);
		window.draw(*oppoLifeBar);

		window.display();
	}

	return EXIT_SUCCESS;
}