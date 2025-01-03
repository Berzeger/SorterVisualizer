#include <iostream>
#include <vector>
#include "sfml_application.h"
#include "sdl_application.h"

int main(int argc, char** argv)
{
	SfmlApplication sfmlApp;
	SdlApplication sdlApp;

	sfmlApp.run();
	//sdlApp.run();

	return 0;
}
