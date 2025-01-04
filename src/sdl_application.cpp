#include "sdl_application.h"
#include <iostream>
#include "bubble_sort.h"

const int kBarWidth = 20;
const int kWindowHeight = 600;
const int kWindowWidth = 800;
const float kDrawInterval = 300.f;

SdlApplication::SdlApplication() :
	m_window(),
	m_renderer(), 
	keepWindowOpen(true), 
	m_event(), 
	m_data{ 67, 53, 88, 34, 61, 151, 192, 142, 66, 243, 27, 223, 194, 223, 38, 242, 48, 21, 237, 77, 224, 146, 101, 74, 8, 127, 119, 128, 48, 132, 83, 15, 18, 37, 28, 8, 94, 72, 93, 217 },
	m_timeSinceLastDraw(0.f)
{
	// Initialize sorter with BubbleSort algorithm
	m_sorter.setSortAlgorithm(std::make_unique<BubbleSort<int>>());
	m_sorter.assignData(m_data);
}

SdlApplication::~SdlApplication()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
	SDL_Quit();
}

void SdlApplication::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize SDL.\n";
		return;
	}

	m_window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	if (!m_window)
	{
		std::cout << "Failed to create window.\n";
		SDL_Quit();
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_renderer)
	{
		std::cout << "Failed to create renderer./n";
		SDL_Quit();
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
	m_timeSinceLastDraw += SDL_GetTicks();

	if (m_timeSinceLastDraw >= kDrawInterval)
	{
		m_sorter.sortStep();
		m_timeSinceLastDraw = 0.f;
	}
}

void SdlApplication::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // set black color
	SDL_RenderClear(m_renderer); // background

	const auto& data = m_sorter.getData();
	size_t nData = data.size();
	for (size_t i = 0; i < nData; ++i)
	{
		float barHeight = static_cast<float>(data[i] * 2 + 1);

		if (m_sorter.getLastMovedIndex() == i)
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // red rectangle
		}
		else
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // white rectangle
		}

		SDL_Rect rect;
		rect.x = i * kBarWidth;
		rect.y = kWindowHeight - barHeight;
		rect.w = kBarWidth;
		rect.h = barHeight;

		SDL_RenderFillRect(m_renderer, &rect);
	}

	SDL_RenderPresent(m_renderer);
}