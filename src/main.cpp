#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {

	// Create the main world (random resolution for now)
	sf::RenderWindow window(sf::VideoMode(800, 600), "Duel Screen", sf::Style::Fullscreen);

	// create a view centered in 0,0, res 800*600
	sf::View view(sf::FloatRect(0, 0, 800, 600));

	// activate it
	window.setView(view);

	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("./img/Mario_Nintendo.png"))
		return EXIT_FAILURE;
	sf::Sprite sprite(texture);
	sprite.move(200, 50);

	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("./fnt/blk_dmd.ttf"))
		return EXIT_FAILURE;
	sf::Text text("This thing works!", font, 50);
	text.move(300, 400);

	// Create a green circle for its own sake
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("./sng/song.ogg"))
		return EXIT_FAILURE;
	music.setLoop(true);

	// Start the game loop
	while (window.isOpen()) {

		 // Process events
		sf::Event event;
		while (window.pollEvent(event)) {

			// LEFT CLICK: Play the music
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) 
					music.play();
				if (event.mouseButton.button == sf::Mouse::Right) 
					music.pause();
			}

			// ESC BUTTON: exit
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();


			// WASD: move the big Mario
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					sprite.move(0, -3);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					sprite.move(-3, 0);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					sprite.move(0, 3);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					sprite.move(3, 0);

			// ARROWS: adjust view
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					view.move(0, -2);
					window.setView(view);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					view.move(0, 2);
					window.setView(view);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					view.move(-2, 0);
					window.setView(view);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					view.move(2, 0);
					window.setView(view);
				}
			}
		}

		window.clear();

		// Draw stuff
		window.draw(sprite);
		window.draw(text);
		window.draw(shape);

		window.display();
	}

	return EXIT_SUCCESS;
}