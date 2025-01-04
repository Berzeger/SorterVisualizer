#include <iostream>
#include <vector>
#include "sfml_application.h"
#include "sdl_application.h"

int main(int argc, char** argv)
{
	SfmlApplication sfmlApp;
	SdlApplication sdlApp;

	Application* app;
	int libChoice;
	LIB_CHOICE:
	std::cout << "Select library:\n1. SFML\n2. SDL\n";
	std::cin >> libChoice;

	switch (libChoice)
	{
	case 1:
		app = new SfmlApplication();
		break;
	case 2:
		app = new SdlApplication();
		break;
	default:
		std::cout << "Unrecognized choice.\n";
		goto LIB_CHOICE;
	}

	app->run();
	delete app;

	return 0; // SDL requires the main function to return, even though standard C++ doesn't need it.
}
