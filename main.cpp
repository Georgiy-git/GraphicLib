#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <iostream>
#include <vector>

#include "EnumProcesses.hpp"
#include "MainProcess.hpp"

#include "Button.hpp"


SDL_Window* window;
SDL_Renderer* render;
int this_process = -1;
std::vector<Object*> objects;


//Процессы
MainProcess* main_process;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	setlocale(LC_ALL, "RU");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("graphic lib", 600, 400, 0, &window, &render);

	main_process = new MainProcess(render);
	this_process = MAIN_PROCESS;

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appstate)
{
	SDL_SetRenderDrawColor(render, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(render);

	switch (this_process) {
	case MAIN_PROCESS:
		main_process->iterate();
	}

	for (auto object : objects) {
		object->iterate();
	}

	SDL_RenderPresent(render);
	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;

	switch (this_process) {
	case MAIN_PROCESS:
		main_process->event(event);
	}

	for (auto object : objects) {
		object->event_process(event);
	}

	return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appstate, SDL_AppResult result) {}