#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <thread>
#include "Object.hpp"
#include "NetworkHandler.hpp"
#include "Line.hpp"
#include "LineEdit.hpp"

class MainProcess
{
public:
	MainProcess(SDL_Renderer* render, NetworkHandler* networkHandler);

	void iterate();

	void event(SDL_Event* event);

private:
	SDL_Renderer* render;
	std::vector<std::shared_ptr<Object>> objects;
	NetworkHandler* networkHandler;
	LineEdit* _lineEdit1;
	Line* _line3;
	bool connected = false;
	std::chrono::steady_clock::time_point tp;
};