#include <string.h>
#include "engine.h"

#define LIFE_GOOD sf::Color(5, 195, 0, 210)
#define LIFE_MMM sf::Color(215, 255, 0, 210)
#define LIFE_BAD sf::Color(248, 2, 40, 210)
#define OPPO_LIFE sf::Color(30, 0, 140, 210)
#define MANA sf::Color(30, 0, 220, 150)

using namespace sf;
using std::vector;

Stage* stage;
Player* player;
Persona* opponent;

Font* font;
Shape* playerLifeBar;
Shape* oppoLifeBar;
Shape* playerManaBar;
vector<Text*> text;

vector<DrawableObj*> toBeDrawn;
vector<ModeledObj*> toBeUpd;
vector<ModeledObj*> playerSide;
vector<ModeledObj*> oppoSide;