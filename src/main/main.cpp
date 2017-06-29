#include <string.h>

#include "headers/main.h"
#include "../loader/load.h"

static Stage* initStage(char* file) {

	char stagePath[256];
	char musicPath[256];
	char skey[] = "BKGD";
	char mkey[] = "TRCK";

	DatFile* f = new DatFile(file);
	f->read(skey, stagePath);
	f->read(mkey, musicPath);

	Stage *stage = new Stage(stagePath, WINDOW_SIZE_X, musicPath);

	stage->music->setLoop(true);
	stage->music->play();
	stage->music->setVolume(100);

	toBeDrawn.push_back(stage);

	return stage;
}

static Player* initPlayer() {
	char marioPath[] = "./img/player.png";

	ControlSet marioControls;
	marioControls.goRight = Keyboard::D;
	marioControls.goLeft = Keyboard::A;
	marioControls.goUp = Keyboard::W;
	marioControls.goDown = Keyboard::S;
	marioControls.teleport = Keyboard::Space;
	marioControls.ability1 = Keyboard::J;
	marioControls.ability2 = Keyboard::K;
	marioControls.ability3 = Keyboard::M;
	marioControls.ability4 = Keyboard::N;

	Stats s;
	s.hp = 100.0;
	s.maxHp = 100.0;
	s.mp = 100;
	s.maxMp = 100.0;
	s.manaRegen = 0.18f;
	s.weigth = 2.0;
	s.collisionDmg = 0.3;
	s.maxSpeed = 8.0;
	s.accel = 1.0;
	s.decel = 1.0;
	s.teleportDist = 150.0;

	Ability n;
	n.dmg = 10.0;
	n.bulletWeight = 10;
	n.bulletSpeed = 5;
	n.shootSpeed = 20;
	n.manaCost = 10;
	strcpy(n.bulletImg, "./img/player.png");
	strcpy(n.bulletExplImg, "./img/bang.png");
	strcpy(n.bulletSoundFx, "./snd/1.wav");
	n.explFrames = 35;
	n.explDecay = 7;
	n.crazyness = 20;

	AbilitySet as;
	as.a1 = n;
	as.a2 = n;
	as.a3 = n;
	as.a4 = n;

	player = new Player(marioPath, s, marioControls, as);
	toBeDrawn.push_back(player);
	toBeUpd.push_back(player);
	playerSide.push_back(player);

	return player;
}

static Persona* initOpponent() {

	char oppoPath[] = "./img/oppo.png";

	Stats s;
	s.hp = 100.0;
	s.maxHp = 100.0;
	s.mp = 100;
	s.maxMp = 100.0;
	s.manaRegen = 0.5f;
	s.weigth = 2.0;
	s.collisionDmg = 0.5;
	s.maxSpeed = 8.0;
	s.accel = 1.0;
	s.decel = 1.0;
	s.teleportDist = 100.0;

	opponent = new Persona(oppoPath, 1000, 500, s);
	toBeDrawn.push_back(opponent);
	toBeUpd.push_back(opponent);
	oppoSide.push_back(opponent);

	return opponent;
}

static void initOverScreen() {

	// read this from proper place
	char opponent[] = "big bad pipa rigata";
	char player[] = "little poor fusillo";

	/**soma magic numbers here*/

	/*skins*/
	char pImg[] = "./img/pbar.png";
	pBar = new Bar(pImg);
	pBar->setSpriteScale(1.8f);
	//pBar->setPos(0.0f, 0.0f);
	
	char oImg[] = "./img/obar.png";
	oBar = new Bar(oImg);
	oBar->setSpriteScale(1.8f);
	oBar->setPos(825.0f, 0.0f);

	/*rectangle fills*/
	playerLifeBar = new RectangleShape(Vector2f(450.0, 30.0));
	playerLifeBar->setPosition(50.0, 50.0);
	playerLifeBar->setFillColor(LIFE_GOOD);
	playerManaBar = new RectangleShape(Vector2f(250.0, 10.0));
	playerManaBar->setPosition(80.0, 80.0);
	playerManaBar->setFillColor(MANA);

	oppoLifeBar = new RectangleShape(Vector2f(430.0, 30.0));
	oppoLifeBar->setOrigin(430.0, 0.0f);
	oppoLifeBar->setPosition(1300.0, 50.0);
	oppoLifeBar->setFillColor(OPPO_LIFE);

	font = new Font();
	font->loadFromFile("./fnt/slp.ttf");

	Text *plName = new Text();
	plName->setFont(*font);
	plName->setString(player);
	plName->setColor(Color(0,26,0,255));
	plName->setCharacterSize(24);
	plName->setPosition(280.0f, 15.0f);

	Text *oppoName = new Text();
	oppoName->setFont(*font);
	oppoName->setString(opponent);
	oppoName->setCharacterSize(24);
	oppoName->setOrigin(24*strlen(opponent), 0.0);
	oppoName->setColor(Color(26,0,0,255));
	oppoName->setPosition(1360.0f, 15.0f);

	text.push_back(plName);
	text.push_back(oppoName);
}

static bool overScreenLogic() {
	float pLifePercent = (float) player->getHp() / (float) player->getMaxHp();
	playerLifeBar->setScale(pLifePercent, 1.0);
	if (pLifePercent < 0.55)
		playerLifeBar->setFillColor(LIFE_MMM);
	if (pLifePercent < 0.26)
		playerLifeBar->setFillColor(LIFE_BAD);

	float pManaPercent = (float) player->getMp() / (float) player->getMaxMp();
	playerManaBar->setScale(pManaPercent, 1.0);
	float oLifePercent = (float) opponent->getHp() / (float) opponent->getMaxHp();
	oppoLifeBar->setScale(oLifePercent, 1.0);

	const float epsilon = 0.5f;
	if (oLifePercent < epsilon)
	{
		playerWon = true;
		return true;
	}

	return pLifePercent < epsilon;
}

static void gameOverHandle() {

	stage->music->stop();
	//play something like fanfare
	
	Text* msg = new Text();
	msg->setFont(*font);
	msg->setCharacterSize(56);

	if (!playerWon)
	{
		msg->setString("YOU LOST. GAME OVER.");
		msg->setColor(Color(240,30,0,255));
	}
	else if (playerWon)
	{
		msg->setString("YOU WON!!!");
		msg->setColor(Color(30,255,15,255));
	}

	//center text
	sf::FloatRect textRect = msg->getLocalBounds();
	msg->setOrigin(textRect.left + textRect.width/2.0f,
	textRect.top  + textRect.height/2.0f);
	msg->setPosition(sf::Vector2f(WINDOW_SIZE_X/2.0f,WINDOW_SIZE_Y/2.0f));

	text.push_back(msg);
}

// ARGS: 1-stage, 2-...
int main(int argc, char* argv[]) {

	if (argc<2)
		return EXIT_FAILURE;

	sf::VideoMode vm = sf::VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// view needs to be same pixels of background!!
	// 'til I find a better way to do it, obviously
	View view(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	window.setView(view);

	stage = initStage(argv[1]);
	player = initPlayer();
	opponent = initOpponent();

	initOverScreen();

	// Start the game loop
	while (window.isOpen()) {

		// life and mana display logic
		gameOver = overScreenLogic();

		if (gameOver)
			gameOverHandle();

		// Process events
		Event event;
		while (window.pollEvent(event)) {

			player->handleControls(event, toBeDrawn, toBeUpd, playerSide);

			if (event.type == Event::KeyPressed) {
				// ESC BUTTON: exit
				if (event.key.code == Keyboard::Escape)
					window.close();

				// P: pause
				if (event.key.code == Keyboard::P) {
					if (gamePaused) {
						gamePaused = false;
					} else {
						gamePaused = true;
					}
				}
			}
		}

		window.clear();

		detectCollisions(playerSide, oppoSide);
		garbageCollection(toBeDrawn, toBeUpd, playerSide, oppoSide);

		if (!gamePaused && !gameOver) {
			for (int i = 0; i < toBeUpd.size(); i++)
				toBeUpd[i]->update(stage->getBound());
		}

		for (int i = 0; i < toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		//draw non game objects here
		window.draw(*playerLifeBar);
		window.draw(*playerManaBar);
		window.draw(*oppoLifeBar);
		pBar -> draw(window);
		oBar -> draw(window);

		for (int i = 0; i < text.size(); i++)
			window.draw(*text[i]);

		window.display();
	}

	return EXIT_SUCCESS;
}