#include "headers/main.h"
#include "headers/overimpr.h"

static Stage* initStage() {
	char stagePath[] = "./img/bkg.png";
	char musicPath[] = "./sng/song.ogg";

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

	Shape* lc = new RectangleShape(Vector2f(pLifeX, pLifeY));
	lc-> setPosition(pLifePosX, pLifePosY);
	lc-> setFillColor(BARS_FILL);
	lc-> setOutlineColor(BARS_CONTOUR);
	lc-> setOutlineThickness(contourThickness);
	contours.push_back(lc);

	Shape* mc = new RectangleShape(Vector2f(pManaX, pManaY));
	mc-> setPosition(pManaPosX, pManaPosY);
	mc-> setFillColor(BARS_FILL);
	mc-> setOutlineColor(BARS_CONTOUR);
	mc-> setOutlineThickness(contourThickness);
	contours.push_back(mc);

	Shape* oc = new RectangleShape(Vector2f(oX, oY));
	oc-> setPosition(oPosX, oPosY);
	oc->setOrigin(oX, 0.0f);
	oc-> setFillColor(BARS_FILL);
	oc-> setOutlineColor(BARS_CONTOUR);
	oc-> setOutlineThickness(contourThickness);
	contours.push_back(oc);

	playerLifeBar = new RectangleShape(Vector2f(pLifeX, pLifeY));
	playerLifeBar->setPosition(pLifePosX, pLifePosY);
	playerLifeBar->setFillColor(LIFE_GOOD);
	playerManaBar = new RectangleShape(Vector2f(pManaX, pManaY));
	playerManaBar->setPosition(pManaPosX, pManaPosY);
	playerManaBar->setFillColor(MANA);

	oppoLifeBar = new RectangleShape(Vector2f(oX, oY));
	oppoLifeBar->setOrigin(oX, 0.0f);
	oppoLifeBar->setPosition(oPosX, oPosY);
	oppoLifeBar->setFillColor(OPPO_LIFE);

	font = new Font();
	font->loadFromFile("./fnt/ancherr.ttf");

	Text *plName = new Text();

	plName->setFont(*font);
	plName->setString("LITTLE POOR FUSILLOH");
	plName->setCharacterSize(36);
	plName->setPosition(40, 0);

	Text *oppoName = new Text();

	oppoName->setFont(*font);
	oppoName->setString("BIG BAD PIPA RIGATAH");
	oppoName->setCharacterSize(36);
	oppoName->setPosition(1000, 0);

	text.push_back(plName);
	text.push_back(oppoName);
}

static void overScreenLogic() {
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
}

int main() {

	sf::VideoMode vm = sf::VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// view needs to be same pixels of background!!
	// 'til I find a better way to do it, obviously
	View view(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	window.setView(view);

	stage = initStage();
	player = initPlayer();
	opponent = initOpponent();

	initOverScreen();

	gamePaused = false;

	// Start the game loop
	while (window.isOpen()) {

		// life and mana display logic
		overScreenLogic();

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

		if (!gamePaused) {
			for (int i = 0; i < toBeUpd.size(); i++)
				toBeUpd[i]->update(stage->getBound());
		}

		for (int i = 0; i < toBeDrawn.size(); i++)
			toBeDrawn[i]->draw(window);

		//draw non game objects here
		window.draw(*playerLifeBar);
		window.draw(*playerManaBar);
		window.draw(*oppoLifeBar);
		for (int i = 0; i < contours.size(); i++)
			window.draw(*contours[i]);
		for (int i = 0; i < text.size(); i++)
			window.draw(*text[i]);

		window.display();
	}

	return EXIT_SUCCESS;
}