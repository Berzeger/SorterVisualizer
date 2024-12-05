#include <SFML/Window.hpp>
#include <iostream>
#include "Sorter.h"
#include "BubbleSort.h"
#include <vector>

int main(int argc, char** argv) 
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Clock deltaClock;

	std::vector<int> arr = { 10, 3, 81, 24, 25, 65, 53, 2, 5, 6, 1, 0, 42, 245, 23, 91, 32 };
	Sorter<int> sorter;
	std::unique_ptr<Sort<int>> bubbleSort = std::make_unique<BubbleSort<int>>();
	sorter.setSortAlgorithm(std::move(bubbleSort));
	sorter.sort(arr);
	sorter.print(arr);

	while (window.isOpen()) {
		sf::Event event;
		//std::cout << "delta time = " << deltaClock.restart().asSeconds() << std::endl;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
}