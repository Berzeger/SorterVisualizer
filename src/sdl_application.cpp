#include "sdl_application.h"
#include <iostream>

SdlApplication::SdlApplication() : m_window(), m_windowSurface(), keepWindowOpen(true), m_event() {}

SdlApplication::~SdlApplication()
{
	SDL_FreeSurface(m_windowSurface);
	SDL_DestroyWindow(m_window);
}

void SdlApplication::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		return;
	}

	m_window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	if (!m_window)
	{
		std::cout << "Failed to create window" << std::endl;
		return;
	}

	m_windowSurface = SDL_GetWindowSurface(m_window);

	if (!m_windowSurface)
	{
		std::cout << "Failed to get the surface from the window" << std::endl;
		return;
	}
}

void SdlApplication::run()
{
	init();

	while (keepWindowOpen)
	{
		handleEvents();
		update();
		render();
	}
}

void SdlApplication::handleEvents()
{
	while (SDL_PollEvent(&m_event) > 0)
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			keepWindowOpen = false;
			break;
		}
	}
}

void SdlApplication::update()
{
}

void SdlApplication::render()
{
	SDL_UpdateWindowSurface(m_window);
}