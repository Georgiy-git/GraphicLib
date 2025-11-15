#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <memory>

class Object;

class MainProcess
{
public:
	MainProcess(SDL_Renderer* render);

	void iterate();

	void event(SDL_Event* event);

private:
	SDL_Renderer* render;
	std::vector<std::shared_ptr<Object>> objects;
};