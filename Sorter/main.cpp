#include <SFML/Window.hpp>
#include <iostream>

int main(int argc, char** argv) 
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Clock deltaClock;

	while (window.isOpen()) {
		sf::Event event;
		std::cout << "delta time = " << deltaClock.restart().asSeconds() << std::endl;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
}