#include <stdio.h>

#include "main.h"
#include "characters.h"

//#define DEBUG

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
Bar* initPlayerBar();
Bar* initOppoBar();
Shape* initPlayerHp();
Shape* initPlayerMp();
Shape* initOppoHp();
Text* initPlayerName(char* file, Font* font, vector<Text*> &text);
Text* initOppoName(char* file, Font* font, vector<Text*> &text);

void garbageCollection(vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void detectCollisions(vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
void removeOutOfField(sf::FloatRect bound, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide, vector<ModeledObj*> &oppoSide);
