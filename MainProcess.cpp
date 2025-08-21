

#include "MainProcess.hpp"
#include "Button.hpp"
#include "Panel.hpp"

MainProcess::MainProcess(SDL_Renderer* render)
	: render{render}
{
	Panel* panel = new Panel(render, 10, 10, 0, 0);
	panel->render_frame(true);
	objects.push_back(panel);

	for (int i = 0; i < 4; ++i) {
		std::shared_ptr<Button> button = std::make_shared<Button>(render, 0, 0, 60, 60);
		button->render_frame(true);
		button->set_frame_color(255, 0, 0, 0);
		button->set_texture("textures\\rect_button.png", 300, 300);
		button->set_pressing_flag(true);
		panel->add(button);
	}
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