#include "sdl_application.h"
#include <iostream>
#include "../sorting_algorithms/bubble_sort.h"
#include "../sorting_algorithms/insertion_sort.h"
#include "../sorting_algorithms/quick_sort.h"

const int kWindowHeight = 600;
const int kWindowWidth = 810;
const int kDrawInterval = 10;

SdlApplication::SdlApplication() :
	m_window(),
	m_renderer(),
	m_keepWindowOpen(true),
	m_event(),
	m_audioDeviceId(0),
	m_timeLastFrame(0.f)
{
	m_timeSinceLastDraw = 0.f;
	m_currentSnapshotIndex = 0;
	m_data = { 67, 53, 88, 34, 61, 151, 192, 142, 66, 243,
	27, 223, 194, 223, 38, 242, 48, 21, 237, 77,
	224, 146, 101, 74, 8, 127, 119, 128, 48, 132,
	83, 15, 18, 37, 28, 8, 94, 72, 93, 217,
	56, 130, 85, 159, 202, 45, 110, 175, 59, 210,
	134, 199, 12, 89, 145, 203, 54, 176, 29, 68,
	116, 39, 162, 207, 23, 150, 91, 184, 140, 33,
	157, 121, 69, 98, 205, 84, 3, 156, 222, 115,
	178, 50, 189, 104, 11, 190, 60, 136, 197, 51,
	124, 173, 95, 182, 44, 168, 79, 153, 224, 7,
	167, 134, 146, 63, 212, 30, 108, 191, 75, 139,
	166, 124, 161, 22, 189, 49, 116, 138, 185, 64,
	214, 157, 31, 83, 196, 102, 25, 179, 71, 189,
	117, 143, 55, 126, 190, 87, 205, 20, 99, 154,
	58, 121, 189, 40, 164, 107, 13, 148, 196, 81,
	203, 34, 175, 96, 218, 49, 133, 180, 77, 161,
	5, 112, 190, 36, 207, 89, 130, 144, 61, 198,
	72, 167, 119, 29, 185, 103, 154, 46, 176, 85,
	210, 38, 141, 192, 66, 229, 14, 123, 181, 57,
	200, 82, 155, 47, 169, 109, 19, 178, 93, 140,
	65, 215, 24, 135, 187, 52, 204, 97, 173, 8,
	161, 59, 190, 43, 222, 76, 128, 116, 84, 199,
	35, 150, 209, 62, 176, 109, 17, 194, 90, 138,
	70, 213, 26, 164, 188, 53, 207, 101, 179, 32,
	145, 210, 61, 182, 111, 39, 196, 85, 175, 44,
	223, 68, 152, 114, 89, 205, 21, 133, 199, 58,
	170, 104, 16, 189, 73, 218, 49, 161, 126, 95
	};
	m_barWidth = kWindowWidth / m_data.size();
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

	m_window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWindowWidth, kWindowHeight, 0);

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

void SdlApplication::run(std::unique_ptr<SortingAlgorithm> sortAlgorithm)
{
	m_sortAlgorithm = std::move(sortAlgorithm);
	m_sortAlgorithm->sort(m_data);
	init();

	while (m_keepWindowOpen)
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
			m_keepWindowOpen = false;
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
		const std::vector<std::vector<int>>& snapshots = m_sortAlgorithm->getSnapshots();
		if (m_currentSnapshotIndex < snapshots.size() - 1 && !snapshots.empty())
		{
			const std::vector<int>& currentArr = snapshots[m_currentSnapshotIndex];

			int frequency = 200 + (currentArr[m_sortAlgorithm->getSwaps()[m_currentSnapshotIndex]] * 10);
			if (frequency > 32767) frequency = 32767; // Beep max frequency
			beep(frequency, kDrawInterval);
			m_currentSnapshotIndex++;
		}

		m_timeSinceLastDraw = 0.f;
	}
}

void SdlApplication::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // set black color
	SDL_RenderClear(m_renderer); // background

	const std::vector<std::vector<int>>& snapshots = m_sortAlgorithm->getSnapshots();
	const std::vector<int>& data = snapshots[m_currentSnapshotIndex];
	size_t nData = data.size();

	if (snapshots.size() > 0) 
	{
		for (size_t i = 0; i < nData; ++i)
		{
			float barHeight = static_cast<float>(data[i] * 2 + 1);

			if (m_sortAlgorithm->getSwaps()[m_currentSnapshotIndex] == i)
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // red rectangle
			}
			else
			{
				SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // white rectangle
			}

			SDL_Rect rect;
			rect.x = i * m_barWidth;
			rect.y = kWindowHeight - barHeight;
			rect.w = m_barWidth;
			rect.h = barHeight;

			SDL_RenderFillRect(m_renderer, &rect);
		}
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

	if (fadeSamples * 2 > length)
	{
		fadeSamples = length / 4;
	}

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
	//SDL_Delay(durationMs);
}