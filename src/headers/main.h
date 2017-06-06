#include <string.h>
#include "engine.h"

using namespace sf;
using std::vector;

#define WINDOW_SIZE_X 1366
#define WINDOW_SIZE_Y 768

bool gamePaused;

#define LIFE_GOOD Color(5, 195, 0, 210)
#define LIFE_MMM Color(215, 255, 0, 210)
#define LIFE_BAD Color(248, 2, 40, 210)
#define OPPO_LIFE Color(30, 0, 140, 210)
#define MANA Color(30, 0, 220, 150)

#define BARS_FILL Color::Transparent
#define BARS_CONTOUR Color::Black
float contourThickness = 1.2f;
float pLifeX = 400.0f;
float pLifeY = 30.0f;
float pLifePosX = 20.0f;
float pLifePosY = 15.0f;
float pManaX = 350.0f;
float pManaY = 25.0f;
float pManaPosX = pLifePosX;
float pManaPosY = 46.0f;
float oX = 500.0f;
float oY = 42.5f;
float oPosX = 1346.0f;
float oPosY = 15.0f;

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