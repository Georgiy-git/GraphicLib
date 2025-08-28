#include "PressButtonGroup.hpp"
#include "Object.hpp"


void PressButtonGroup::event_process(SDL_Event* event) 
{
	if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || 
		event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		for (auto button : buttons) {
			if (button->inside() && button != pressing) {
				press(button);
				break;
			}
		}
	}
}

void PressButtonGroup::press(Button* button)
{
	if (pressing != nullptr) pressing->remove_pressing();
	pressing = button;
}

void PressButtonGroup::add(Button* button)
{
	buttons.push_back(button);
	button->set_pressing_flag(true);
}

void PressButtonGroup::clear() {
	buttons.clear();
}
