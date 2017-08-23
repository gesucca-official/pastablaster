#include <iostream>
#include <stdlib.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WINDOW_X 1366
#define WINDOW_Y 768

using namespace sf;

Texture bkg_t;
Sprite* bkg_s;

static Sprite* initBkg() {
	bkg_t.loadFromFile("./img/title.jpg");
	bkg_t.setSmooth(true);
	bkg_s = new Sprite(bkg_t);
	int ratio = WINDOW_X / (bkg_s->getTexture()->getSize().x);
	bkg_s->setScale(ratio, ratio);
	bkg_s->setColor(Color(90,90,90,255));
	return bkg_s;
}

Text* title;
Font* title_font;

static Text* initTitle() {
	title = new Text();
	title_font = new Font();
	title_font->loadFromFile("./fnt/slp_bold.ttf");
	title->setFont(*title_font);
	title->setCharacterSize(114);
	title->setString("P A S T A  B L A S T E R");
	title->setColor(Color(130,110,160,252));
	title->setPosition(120, 50);
	return title;
}

Text* subtitle;
Font* subtitle_font;

static Text* initSubTitle() {
	subtitle= new Text();
	subtitle_font = new Font();
	subtitle_font->loadFromFile("./fnt/slp_bold_it.ttf");
	subtitle->setFont(*subtitle_font);
	subtitle->setCharacterSize(56);
	subtitle->setString("D  E  M  O");
	subtitle->setColor(Color(155,99,55,250));
	subtitle->setPosition(560, 200);
	return subtitle;
}

Text* footer;
Font* footer_font;

static Text* initFooter() {
	footer = new Text();
	footer_font = new Font();
	footer_font->loadFromFile("./fnt/ancherr.ttf");
	footer->setFont(*footer_font);
	footer->setCharacterSize(55);
	footer->setString("PRESS ENTER TO PLAY THE DEMO STAGE\n 	  PRESS ESC TO QUIT GAME");
	footer->setColor(Color(220,29,25,245));
	footer->setPosition(400, 620);
	return footer;
}

Text* instruction;
Font* instruction_font;

static Text* initInstruction() {
	Text* instruction= new Text();
	Font* instruction_font = new Font();
	instruction_font->loadFromFile("./fnt/slp.ttf");
	instruction->setFont(*instruction_font);
	instruction->setCharacterSize(30);
	instruction->setString("W A S D - move the little poor fusilloh\n        J - fire a big straight shot\n K - fire four small shots around you\n         N - fire a big, crazy bullet\n     M - fire four small crazy bullets");
	instruction->setColor(Color(55,199,55,250));
	instruction->setPosition(420, 360);
	return instruction;
}

int main(int argc, char* argv[]) {

	VideoMode vm = VideoMode().getDesktopMode();
	RenderWindow window(vm, "Duel Screen", Style::Fullscreen);
	window.setFramerateLimit(60);
	View view(FloatRect(0, 0, WINDOW_X, WINDOW_Y));
	window.setView(view);

	Music* music = new Music();
	music->openFromFile("./snd/title.ogg");
	music->setVolume(50);
	music->setLoop(true);
	music->play();

	bkg_s = initBkg();
	title = initTitle();
	subtitle = initSubTitle();
	footer = initFooter();
	instruction = initInstruction();

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Return) {
					window.close();
					music->stop();
					system("./bin/combat ./dat/demo.stage ./dat/demo.player ./dat/demo.opponent");
					return 0;
				}

				if (event.key.code == Keyboard::Escape) {
					return 0;
				}
			}
		}

		window.draw(*bkg_s);
		window.draw(*title);
		window.draw(*subtitle);
		window.draw(*instruction);
		window.draw(*footer);

		window.display();
	}
	return 0;
}