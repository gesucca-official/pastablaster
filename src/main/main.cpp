#include "headers/main.h"
#include "headers/characters.h"

#define DEBUG

#ifdef DEBUG
	#include <stdio.h>
#endif

using namespace sf;
using std::vector;

Stage* stage;
Player* player;
Persona* opponent;

Shape* playerLifeBar;
Shape* oppoLifeBar;
Shape* playerManaBar;
Bar* pBar;
Bar* oBar;

Font* font;
vector<Text*> text;

vector<DrawableObj*> toBeDrawn;
vector<ModeledObj*> toBeUpd;
vector<ModeledObj*> playerSide;
vector<ModeledObj*> oppoSide;

bool gamePaused = false;
bool gameOver = false;
bool playerWon = false;

Stage* initStage(char* file, vector<DrawableObj*> &toBeDrawn);
Player* initPlayer(char* file, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide);
Persona* initOpponent(char* file, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide);
void initOverScreen(Bar *pBar, Bar *oBar, Shape *playerLifeBar, Shape *oppoLifeBar, Shape *playerManaBar, Font * font, vector<Text*> &text);

void garbageCollection(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void detectCollisions(vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void removeOutOfField(sf::FloatRect bound, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);

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

	if (argc!=4)
	{
		printf("INCORRECT NUMBER OF ARGUMENTS - what the hell are you trying to do?");
		return EXIT_FAILURE;
	}

	stage = initStage(argv[1], toBeDrawn);
	player = initPlayer(argv[2], toBeDrawn, toBeUpd, playerSide);
	opponent = initOpponent(argv[3], toBeDrawn, toBeUpd, oppoSide);

	//split iiiiiiit
	//initOverScreen(pBar, oBar, playerLifeBar, oppoLifeBar, playerManaBar, font, text);

	// Start the game loop
	while (window.isOpen()) {

		// life and mana display logic
		//gameOver = overScreenLogic();

		//if (gameOver)
		//	gameOverHandle();

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
		/*window.draw(*playerLifeBar);
		window.draw(*playerManaBar);
		window.draw(*oppoLifeBar);
		pBar -> draw(window);
		oBar -> draw(window);

		for (int i = 0; i < text.size(); i++)
			window.draw(*text[i]);
*/
		window.display();
	}
	return EXIT_SUCCESS;
}