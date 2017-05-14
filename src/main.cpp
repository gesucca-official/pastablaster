#include <SFML/Audio.hpp>

#include "Player.hpp"

using namespace sf;

int main() {

	// Create the main world (random resolution for now)
	RenderWindow window(VideoMode(800, 600), "Duel Screen", Style::Fullscreen);

	// create a view centered in 0,0, res 800*600
	View view(FloatRect(0, 0, 800, 600));

	// activate it
	window.setView(view);

	//try drawable obj
	char lanscapePath[] = "./img/ground.jpg";
	DrawableObj landscape(lanscapePath);

	//another big mario
	char marioPath[] = "./img/Mario_Nintendo.png";
	Player mario(marioPath);

	// Load a big mario to display
	Texture texture;
	if (!texture.loadFromFile("./img/Mario_Nintendo.png"))
		return EXIT_FAILURE;
	Sprite bigMario(texture);
	bigMario.move(200, 50);
	bool isMarioJumping = false;
	int jumpSpan = 25;
	int preJumpY;

	// Create a graphical text to display
	Font font;
	if (!font.loadFromFile("./fnt/blk_dmd.ttf"))
		return EXIT_FAILURE;
	Text text("This thing works!", font, 50);
	text.move(300, 400);

	// Create a green circle for its own sake
	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	// Load a music to play
	Music music;
	if (!music.openFromFile("./sng/song.ogg"))
		return EXIT_FAILURE;
	music.setLoop(true);

	// Start the game loop
	while (window.isOpen()) {

		// Jump handle
		if (isMarioJumping) {
				if ((bigMario.getPosition().y+jumpSpan) > preJumpY)
				bigMario.move(0, -5);
			else
				// return the fuck down!!
				isMarioJumping = false;
		}

		 // Process events
		Event event;
		while (window.pollEvent(event)) {

			mario.handleControls(event);

			// LEFT CLICK: Play the music
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) 
					music.play();
				if (event.mouseButton.button == Mouse::Right) 
					music.pause();
			}

			// ESC BUTTON: exit
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Escape)
					window.close();

			// WASD: move the big Mario
				if (Keyboard::isKeyPressed(Keyboard::W))
					bigMario.move(0, -3);
				if (Keyboard::isKeyPressed(Keyboard::A))
					bigMario.move(-3, 0);
				if (Keyboard::isKeyPressed(Keyboard::S))
					bigMario.move(0, 3);
				if (Keyboard::isKeyPressed(Keyboard::D))
					bigMario.move(3, 0);

			// JUMP WITH SPACE
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					isMarioJumping = true;
					preJumpY = bigMario.getPosition().y;
					//std::cout << preJumpY;
				}

			// ARROWS: adjust view
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					view.move(0, -2);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					view.move(0, 2);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					view.move(-2, 0);
					window.setView(view);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					view.move(2, 0);
					window.setView(view);
				}
			}
		}

		window.clear();

		landscape.draw(window);
		mario.draw(window);

		// Draw stuff
		window.draw(bigMario);
		window.draw(text);
		window.draw(shape);

		window.display();
	}

	return EXIT_SUCCESS;
}

/*
class Mario {
public:
   void Jump();
   void Draw(RenderWindow &Window);
   void Update();
private:
   sf::Sprite Sprite;
   bool IsJumping;
};

void Mario::Jump() {
   IsJumping = true;
}

void Mario::Update() {
   if(IsJumping) {
      same jumping logic as above
   }
   
   some more updating logic
}
*/

/*
int main()
{
    vector<string> list;
    list.push_back("foo");
    list.push_back("bar");
    for( vector<string>::const_iterator it = list.begin(); it != list.end(); ++it )
        cout << *it << endl;

    return 0;
}
*/