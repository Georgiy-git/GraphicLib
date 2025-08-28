#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "Button.hpp"


class PressButtonGroup
{
public:
	void event_process(SDL_Event* event);

	//Снимает зажатие с зажатой кнопки и в pressing помещает новую.
	void press(Button* button);

	void add(Button* button);

	//Очищает вектор buttons.
	void clear();

	std::vector<Button*> buttons;
	Button* pressing = nullptr;
};

