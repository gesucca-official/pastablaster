#include "headers/main_decl.h"

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
	if (oLifePercent < epsilon)	{
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

	if (!playerWon)	{
		msg->setString("YOU LOST. GAME OVER.");
		msg->setColor(Color(240,30,0,255));
	}
	else if (playerWon)	{
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

// ARGS: 1-stage, 2-player, 3-opponent
int main(int argc, char* argv[]) {

	#ifdef DEBUG
		printf("ARGV value: %d\n", argc);
		int i;
		for (i = 0; i < argc; i++)
			printf("%s\n", argv[i]);
	#endif

	sf::VideoMode vm = sf::VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);

	// view needs to be same pixels of background!!
	// 'til I find a better way to do it, obviously
	View view(FloatRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y));
	window.setView(view);

	if (argc!=4) {
		printf("INCORRECT NUMBER OF ARGUMENTS - what the hell are you trying to do?");
		return EXIT_FAILURE;
	}

	stage = initStage(argv[1], toBeDrawn);
	player = initPlayer(argv[2], toBeDrawn, toBeUpd, playerSide);
	opponent = initOpponent(argv[3], toBeDrawn, toBeUpd, oppoSide);

	font = new Font();
	font->loadFromFile("./fnt/slp.ttf");
	initPlayerName(argv[2], font, text);
	initOppoName(argv[3], font, text);

	pBar = initPlayerBar();
	oBar = initOppoBar();

	playerLifeBar = initPlayerHp();
	playerManaBar = initPlayerMp();
	oppoLifeBar = initOppoHp();

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

		// over screen life bars
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