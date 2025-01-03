#pragma once

class Application
{
public:
	virtual ~Application() {};

	virtual void run() = 0;

protected:
	virtual void init() = 0;
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};