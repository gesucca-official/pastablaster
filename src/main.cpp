#include "headers/main.h"

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

void initOverScreen() {
	playerLifeBar = new RectangleShape(sf::Vector2f(400, 30));
	playerLifeBar->setPosition(20, 15);
	playerLifeBar->setFillColor(LIFE_GOOD);
	playerManaBar = new RectangleShape(sf::Vector2f(350, 25));
	playerManaBar->setPosition(20, 45);
	playerManaBar->setFillColor(MANA);

	oppoLifeBar = new RectangleShape(sf::Vector2f(500, 42.5));
	oppoLifeBar->setOrigin(500, 0);
	oppoLifeBar->setPosition(1346, 15);
	oppoLifeBar->setFillColor(OPPO_LIFE);

	font = new Font();
	font->loadFromFile("./fnt/ancherr.ttf");

	Text *plName = new Text();

	plName->setFont(*font);
	plName->setString("LITTLE POOR FUSILLOH");
	plName->setCharacterSize(36); 
	plName->setPosition(40,0);

	Text *oppoName = new Text();

	oppoName->setFont(*font);
	oppoName->setString("BIG BAD PIPA RIGATAH");
	oppoName->setCharacterSize(36);
	oppoName->setPosition(1000,0);
	
	text.push_back(plName);
	text.push_back(oppoName);
}

void overScreenLogic() {
	float pLifePercent = (float) player->getHp() / (float) player->getMaxHp();
	playerLifeBar->setScale(pLifePercent, 1.0);
	if (pLifePercent<0.55)
		playerLifeBar->setFillColor(LIFE_MMM);
	if (pLifePercent<0.26)
		playerLifeBar->setFillColor(LIFE_BAD);

	float pManaPercent = (float) player->getMp() / (float) player->getMaxMp();
	playerManaBar->setScale(pManaPercent, 1.0);
	float oLifePercent = (float) opponent->getHp() / (float) opponent->getMaxHp();
	oppoLifeBar->setScale(oLifePercent, 1.0);
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

	initOverScreen();

	// Start the game loop
	while (window.isOpen()) {

		// life and mana display logic
		overScreenLogic();

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

		detectCollisions(playerSide, oppoSide);
		garbageCollection(toBeDrawn, toBeUpd, playerSide, oppoSide);

		//update and draw game object
		for (int i=0; i<toBeUpd.size(); i++)
			toBeUpd[i]->update(stage->getBound());
		for (int i=0; i<toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		//draw non game objects here
		window.draw(*playerLifeBar);
		window.draw(*playerManaBar);
		window.draw(*oppoLifeBar);
		for (int i=0; i<text.size(); i++)
			window.draw(*text[i]);

		window.display();
	}

	return EXIT_SUCCESS;
}