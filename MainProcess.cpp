

#include "MainProcess.hpp"
#include "Button.hpp"


MainProcess::MainProcess(SDL_Renderer* render)
	: render{render}
{
	Button* button = new Button(render, 100, 100, 200, 200);
	button->render_frame(true);
	button->set_texture("textures\\rect_button.png", 300, 300);
	button->set_pressing_flag(true);
	objects.push_back(button);
}

void MainProcess::iterate() {
	for (auto object : objects) {
		object->iterate();
	}
}

void MainProcess::event(SDL_Event* event) {
	for (auto object : objects) {
		object->event_process(event);
	}

	if (event->type == SDL_EVENT_MOUSE_MOTION) {

	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {

	}
}