#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include <iostream>
#include <vector>
#include <thread>

#include "NetworkHandler.hpp"

#include "EnumProcesses.hpp"
#include "MainProcess.hpp"

#include "Button.hpp"
#include "Line.hpp"

//Базовые переменные.
SDL_Window* window;
SDL_Renderer* render;
extern int this_process;
std::vector<Object*> objects;
NetworkHandler networkHandler;

//Процессы.
MainProcess* main_process;

//Пользовательские переменные.
Object* wrap_button;
Object* close_button;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	std::locale::global(std::locale("RU"));
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("", 0, 0, SDL_WINDOW_FULLSCREEN, &window, &render);

	Line::set_default_font(render);

	std::thread([]() {
		networkHandler.context.run();
		}).detach();	

	main_process = new MainProcess(render, &networkHandler);
	this_process = MAIN_PROCESS;

	auto display_size = Object::get_display_size();

	wrap_button = new Button(render, display_size.first - 200, 0, 100, 60);
	auto wrap_button_texture = IMG_LoadTexture(render, "textures\\anim_wrap_button.png");
	wrap_button->set_texture(wrap_button_texture, 500, 300);
	objects.push_back(wrap_button);

	close_button = new Button(render, display_size.first - 100, 0, 100, 60);
	auto close_button_texture = IMG_LoadTexture(render, "textures\\anim_button_close.png");
	close_button->set_texture(close_button_texture, 500, 300);
	objects.push_back(close_button);

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
		object->process_event(event);
	}

	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		if (wrap_button->in()) wrap_button->start_animation(0, 6, 30);
		else if (wrap_button->out()) wrap_button->start_animation(1, 6, 30);

		if (close_button->in()) close_button->start_animation(0, 6, 30);
		else if (close_button->out()) close_button->start_animation(1, 6, 30);
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (close_button->cursor_inside()) {
			return SDL_APP_SUCCESS;
		}
		if (wrap_button->cursor_inside()) {
			SDL_MinimizeWindow(window);
		}
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {

	}

	return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appstate, SDL_AppResult result) 
{

}