#include <string.h>

#include "headers/main.h"
#include "../loader/load.h"

static Stage* initStage(char* file) {

	char stagePath[256];
	char musicPath[256];
	char skey[] = "BKGD", mkey[] = "TRCK";

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

static Player* initPlayer(char* file) {

	DatFile* plFile = new DatFile(file);
	char hp[] = "MXHP", mp[] = "MXMP", regen[] = "MNRG", weight[] = "WGHT",
	collDmg[] = "CLLD", spe[] = "MXSP", acc[] = "ACCL", dec[] = "DCCL", tele[] = "TLPT";

	Stats s;
	s.maxHp = plFile->read(hp);
	s.hp = s.maxHp;
	s.maxMp = plFile->read(mp);
	s.mp = s.maxMp;
	s.manaRegen = plFile->read(regen);
	s.weigth = plFile->read(weight);
	s.collisionDmg = plFile->read(collDmg);
	s.maxSpeed = plFile->read(spe);
	s.accel = plFile->read(acc);
	s.decel = plFile->read(dec);
	s.teleportDist = plFile->read(tele);
	
	Ability a1, a2, a3, a4;
	Ability cycle[] = {a1, a2, a3, a4};
	int i;
	for (i=0; i<4; i++)
	{
		char ability[64], path[64];
		sprintf(ability, "ABL%d", i+1);
		plFile->read(ability, path);
		DatFile* abFile = new DatFile(path);

		char dmg[] = "DAMG", bweigth[] = "BWGT", bspeed[] = "BSPE", shtspd[] = "SSPE",
		mana[] = "MCST", img[] = "BIMG", eimg[]= "EXPL", sound[] = "SDFX", frames[] = "FRAM", decay[] = "DCAY", crazy[] = "CRZY";
		
		cycle[i].dmg = abFile->read(dmg);
		cycle[i].bulletWeight = abFile->read(bweigth);
		cycle[i].bulletSpeed = abFile->read(bspeed);
		cycle[i].shootSpeed = abFile->read(shtspd);
		cycle[i].manaCost = abFile->read(mana);
		char buffer[64];
		abFile->read(img, buffer);
		strcpy(cycle[i].bulletImg, buffer);
		abFile->read(eimg, buffer);
		strcpy(cycle[i].bulletExplImg, buffer);
		abFile->read(sound, buffer);
		strcpy(cycle[i].bulletSoundFx, buffer);

		cycle[i].explFrames = abFile->read(frames);
		cycle[i].explDecay = abFile->read(decay);
		cycle[i].crazyness = abFile->read(crazy);
	}

	AbilitySet as;
	as.a1 = cycle[0];
	as.a2 = cycle[1];
	as.a3 = cycle[2];
	as.a4 = cycle[3];

	char path[256];
	char key[] = "SPRT";
	plFile->read(key, path);

	/*hard wired for now*/
	ControlSet defaultCtrls;
	defaultCtrls.goRight = Keyboard::D;
	defaultCtrls.goLeft = Keyboard::A;
	defaultCtrls.goUp = Keyboard::W;
	defaultCtrls.goDown = Keyboard::S;
	defaultCtrls.teleport = Keyboard::Space;
	defaultCtrls.ability1 = Keyboard::J;
	defaultCtrls.ability2 = Keyboard::K;
	defaultCtrls.ability3 = Keyboard::M;
	defaultCtrls.ability4 = Keyboard::N;

	player = new Player(path, s, defaultCtrls, as);
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

// ARGS: 1-stage, 2-player, 3-..
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
	player = initPlayer(argv[2]);
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