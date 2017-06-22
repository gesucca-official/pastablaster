#include <string.h>
#include "engine.h"

using namespace sf;
using std::vector;

#define WINDOW_SIZE_X 1366
#define WINDOW_SIZE_Y 768

bool gamePaused;

Stage* stage;
Player* player;
Persona* opponent;

Font* font;
Shape* playerLifeBar;
Shape* oppoLifeBar;
Shape* playerManaBar;
vector<Shape*> contours;
vector<Text*> text;

vector<DrawableObj*> toBeDrawn;
vector<ModeledObj*> toBeUpd;
vector<ModeledObj*> playerSide;
vector<ModeledObj*> oppoSide;