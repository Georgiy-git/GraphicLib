#include "Button.hpp"

Button::Button(SDL_Renderer* render, float center_x, float center_y, float width, float height)
	: Object(render, center_x, center_y, width, height)
{

}

void Button::event_process(SDL_Event* event)
{
	Object::event_process(event);

	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		if (in() && !pressing) change_show_rect(1, 0);
		else if (out() && !pressing) change_show_rect(0, 0);
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (inside()) {
			if (!pressing && flag_pressing) set_pressing();
			else if (pressing) remove_pressing();
			else change_show_rect(0, 0);
		}
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (inside()) change_show_rect(1, 0);
	}
}

void Button::remove_pressing() {
	pressing = false;
	change_show_rect(0, 0);
}

void Button::set_pressing() {
	pressing = true;
	change_show_rect(1, 0);
}

bool Button::get_pressing_flag() {
	return flag_pressing;
}

void Button::set_pressing_flag(bool flag) {
	flag_pressing = flag;
}
