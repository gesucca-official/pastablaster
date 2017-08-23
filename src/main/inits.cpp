#include <string.h>

#include "headers/main.h"
#include "headers/characters.h"
#include "../loader/load.h"

//#define DEBUG

#ifdef DEBUG
	#include <stdio.h>
#endif

static Stats initStats(char* file) {

	DatFile* plFile = new DatFile(file);

	char hp[] = "MXHP", mp[] = "MXMP", regen[] = "MNRG", weight[] = "WGHT",
		collDmg[] = "CLLD", spe[] = "MXSP", acc[] = "ACCL", dec[] = "DCCL", 
		tele[] = "TLPT", decision[] = "DCSP";

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
	s.decisionPace = plFile->read(decision);

	delete plFile;
	return s;
}

static AbilitySet initAbilities(char* file) {

	DatFile* plFile = new DatFile(file);

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

		delete abFile;
	}

	AbilitySet as;
	as.a1 = cycle[0];
	as.a2 = cycle[1];
	as.a3 = cycle[2];
	as.a4 = cycle[3];

	return as;
}

Stage* initStage(char* file, vector<DrawableObj*> &toBeDrawn) {

	char stagePath[MAX_PATH_LEN];
	char musicPath[MAX_PATH_LEN];
	char skey[] = "BKGD", mkey[] = "TRCK";

	DatFile* f = new DatFile(file);

	f->read(skey, stagePath);
	f->read(mkey, musicPath);

	#ifdef DEBUG
		printf("initStage:\n");
		printf("	img path: %s\n", stagePath);
		printf("	music path: %s\n", musicPath);
	#endif

	Stage *stage = new Stage(stagePath, WINDOW_SIZE_X, musicPath);

	stage->music->setLoop(true);
	stage->music->play();
	stage->music->setVolume(100);

	toBeDrawn.push_back(stage);

	delete f;
	return stage;
}

Player* initPlayer(char* file, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &playerSide) {

	Stats s = initStats(file);
	AbilitySet as = initAbilities(file);
	
	DatFile* plFile = new DatFile(file);

	char path[MAX_PATH_LEN];
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
	defaultCtrls.ability3 = Keyboard::N;
	defaultCtrls.ability4 = Keyboard::M;

	Player *player = new Player(path, s, defaultCtrls, as);
	toBeDrawn.push_back(player);
	toBeUpd.push_back(player);
	playerSide.push_back(player);

	delete plFile;
	return player;
}

Opponent* initOpponent(char* file, vector<DrawableObj*> &toBeDrawn, vector<ModeledObj*> &toBeUpd, vector<ModeledObj*> &oppoSide) {

	Stats s = initStats(file);
	AbilitySet as = initAbilities(file);

	DatFile* plFile = new DatFile(file);

	char path[MAX_PATH_LEN];
	char key[] = "SPRT";
	plFile->read(key, path);

	Opponent *opponent = new Opponent(path, s, as);
	toBeDrawn.push_back(opponent);
	toBeUpd.push_back(opponent);
	oppoSide.push_back(opponent);

	delete plFile;
	return opponent;

}

Bar* initPlayerBar() {
	char pImg[] = "./img/pbar.png";
	Bar* pBar = new Bar(pImg);
	pBar->setSpriteScale(1.8f);
	
	return pBar;
}

Bar* initOppoBar() {
	char oImg[] = "./img/obar.png";
	Bar* oBar = new Bar(oImg);
	oBar->setSpriteScale(1.8f);
	oBar->setPos(825.0f, 0.0f);

	return oBar;
}

Shape* initPlayerHp() {
	Shape* playerLifeBar = new RectangleShape(Vector2f(450.0, 30.0));
	playerLifeBar->setPosition(50.0, 50.0);
	playerLifeBar->setFillColor(LIFE_GOOD);

	return playerLifeBar;
}

Shape* initPlayerMp() {
	Shape* playerManaBar = new RectangleShape(Vector2f(250.0, 10.0));
	playerManaBar->setPosition(80.0, 80.0);
	playerManaBar->setFillColor(MANA);

	return playerManaBar;
}

Shape* initOppoHp() {
	Shape* oppoLifeBar = new RectangleShape(Vector2f(430.0, 30.0));
	oppoLifeBar->setOrigin(430.0, 0.0f);
	oppoLifeBar->setPosition(1300.0, 50.0);
	oppoLifeBar->setFillColor(OPPO_LIFE);

	return oppoLifeBar;
}

Text* initPlayerName(char* file, Font* font, vector<Text*> &text) {

	DatFile* plFile = new DatFile(file);

	char name[MAX_PATH_LEN];
	char key[] = "PLNM";
	plFile->read(key, name);

	Text *plName = new Text();
	plName->setFont(*font);
	plName->setString(name);
	plName->setColor(Color(0,26,0,255));
	plName->setCharacterSize(24);
	plName->setPosition(280.0f, 15.0f);

	text.push_back(plName);

	delete plFile;
	return plName;
}

Text* initOppoName(char* file, Font* font, vector<Text*> &text) {

	DatFile* opFile = new DatFile(file);

	char name[MAX_PATH_LEN];
	char key[] = "OPNM";
	opFile->read(key, name);

	Text *oppoName = new Text();
	oppoName->setFont(*font);
	oppoName->setString(name);
	oppoName->setCharacterSize(24);
	oppoName->setOrigin(24*strlen(name), 0.0);
	oppoName->setColor(Color(26,0,0,255));
	oppoName->setPosition(1360.0f, 15.0f);

	text.push_back(oppoName);

	delete opFile;
	return oppoName;
}
