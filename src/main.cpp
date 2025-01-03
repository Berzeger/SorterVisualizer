#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "sorter.h"
#include "bubble_sort.h"
#include <vector>
#include "application.h"

const float kBarWidth = 20.f;
const float kWindowHeight = 600.f;
const float kWindowWidth = 800.f;
const float kDrawInterval = 0.03f;

void SFML() {
	float timeSinceLastDraw = 0.f;

	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(kWindowWidth), static_cast<unsigned int>(kWindowHeight)), "My window");
	sf::Clock deltaClock;

	std::vector<int> arr = { 67, 53, 88, 34, 61, 151, 192, 142, 66, 243, 27, 223, 194, 223, 38, 242, 48, 21, 237, 77, 224, 146, 101, 74, 8, 127, 119, 128, 48, 132, 83, 15, 18, 37, 28, 8, 94, 72, 93, 217 };
	Sorter<int> sorter;
	std::unique_ptr<Sort<int>> bubbleSort = std::make_unique<BubbleSort<int>>();

	sorter.setSortAlgorithm(std::move(bubbleSort));
	sorter.assignData(arr);

	while (window.isOpen()) {
		sf::Event event;
		//std::cout << "delta time = " << deltaClock.restart().asSeconds() << std::endl;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		timeSinceLastDraw += deltaClock.restart().asSeconds();

		if (timeSinceLastDraw >= kDrawInterval) {
			sorter.sortStep();
			timeSinceLastDraw = 0.f;
		}

		window.clear(sf::Color::Black);

		auto data = sorter.getData();
		size_t nData = data.size();
		for (size_t i = 0; i < nData; ++i) {
			int barHeight = data[i] * 2 + 1;
			sf::RectangleShape rectangle(sf::Vector2f(kBarWidth, static_cast<float>(barHeight)));
			if (sorter.getLastMovedIndex() == i) {
				rectangle.setFillColor(sf::Color::Red);
			}
			rectangle.setPosition(sf::Vector2f(i * kBarWidth, kWindowHeight - barHeight));
			window.draw(rectangle);
		}

		window.display();
	}


	//sorter.sort(arr);
	sorter.print(arr);
}

void SDL() {
	Application app;
	app.update();
}

int main(int argc, char** argv) 
{
	//SFML();
	SDL();
	return 0;
}
