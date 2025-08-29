#include "Person.hpp"

Person::Person(SDL_Renderer* render, float corner_x, float corner_y)
	: Object(render, corner_x, corner_y, 80, 300)
{
}

void Person::iterate()
{
}

void Person::event_process(SDL_Event* event)
{
	if (event->type == SDL_EVENT_MOUSE_MOTION) {

	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {

	}
}

void Person::step()
{
}

void Person::turn_around()
{
}

bool Person::inside(float x, float y) const
{
	return false;
}
