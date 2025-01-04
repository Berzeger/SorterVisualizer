#include "sdl_application.h"
#include <iostream>
#include "bubble_sort.h"

const int kBarWidth = 20;
const int kWindowHeight = 600;
const int kWindowWidth = 800;
const int kDrawInterval = 10;

SdlApplication::SdlApplication() :
	m_window(),
	m_renderer(),
	keepWindowOpen(true),
	m_event(),
	m_data{ 67, 53, 88, 34, 61, 151, 192, 142, 66, 243, 27, 223, 194, 223, 38, 242, 48, 21, 237, 77, 224, 146, 101, 74, 8, 127, 119, 128, 48, 132, 83, 15, 18, 37, 28, 8, 94, 72, 93, 217 },
	m_timeSinceLastDraw(0.f),
	m_audioDeviceId(0),
	m_timeLastFrame(0.f)
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
	if (m_audioDeviceId != 0)
	{
		SDL_CloseAudioDevice(m_audioDeviceId);
		m_audioDeviceId = 0;
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

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (!m_renderer)
	{
		std::cout << "Failed to create renderer./n";
		SDL_Quit();
		return;
	}

	initAudio();
}

void SdlApplication::initAudio()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "Failed to initialize SDL audio: "
			<< SDL_GetError() << "\n";
		return;
	}

	SDL_AudioSpec want;
	SDL_zero(want);

	want.freq = 44100;
	want.format = AUDIO_S16SYS;
	want.channels = 1;
	want.samples = 1024;
	want.callback = nullptr;

	SDL_AudioSpec have;
	SDL_zero(have);

	m_audioDeviceId = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
	if (m_audioDeviceId == 0)
	{
		std::cout << "[SDL] Failed to open audio device: " << SDL_GetError() << "\n";
		return;
	}

	std::cout << "freq: " << have.freq
		<< ", format: " << have.format
		<< ", channels: " << (int)have.channels
		<< ", samples: " << have.samples << "\n";

	SDL_PauseAudioDevice(m_audioDeviceId, 0); // start playback
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
	int timeThisFrame = SDL_GetTicks();
	int delta = timeThisFrame - m_timeLastFrame;
	m_timeLastFrame = timeThisFrame;

	m_timeSinceLastDraw += delta;
	std::cout << "ms = " << delta << ", m_timeSinceLastDraw = " << m_timeSinceLastDraw << "\n";

	if (m_timeSinceLastDraw >= kDrawInterval)
	{
		int sortedElem;
		if (m_sorter.sortStep(sortedElem))
		{
			int frequency = 200 + (sortedElem * 20);
			if (frequency > 32767) frequency = 32767; // Beep max frequency
			beep(frequency, kDrawInterval);
		}
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

void SdlApplication::beep(int frequency, int durationMs)
{
	if (m_audioDeviceId == 0)
	{
		return;
	}

	const int sampleRate = 44100;
	const int amplitude = 28000;
	const int length = (sampleRate * durationMs) / 1000;

	std::vector<Sint16> buffer(length);

	double phaseIncrement = (2.f * M_PI * frequency) / sampleRate;
	double phase = 0.f;
	int fadeSamples = sampleRate / 200; // 5 ms fade, prevents crackling

	for (int i = 0; i < length; ++i)
	{
		double envelope = 1.0;

		// Fade in
		if (i < fadeSamples)
		{
			envelope = i / static_cast<double>(fadeSamples);
		}
		// Fade out
		else if (i > length - fadeSamples)
		{
			envelope = (length - i) / static_cast<double>(fadeSamples);
		}
		buffer[i] = static_cast<Sint16>(envelope * amplitude * std::sin(phase));
		phase += phaseIncrement;
	}

	SDL_QueueAudio(m_audioDeviceId, buffer.data(), buffer.size() * sizeof(Sint16));
	SDL_Delay(durationMs);
}