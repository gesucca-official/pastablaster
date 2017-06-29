#include "engine.h"

using namespace sf;
using std::vector;

#define WINDOW_SIZE_X 1366
#define WINDOW_SIZE_Y 768

#define LIFE_GOOD Color(5, 205, 0, 220)
#define LIFE_MMM Color(215, 255, 0, 220)
#define LIFE_BAD Color(248, 2, 40, 220)
#define OPPO_LIFE Color(30, 0, 140, 220)
#define MANA Color(6, 115, 245, 210)

bool gamePaused = false;
bool gameOver = false;
bool playerWon = false;

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