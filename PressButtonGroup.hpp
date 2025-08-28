#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "Button.hpp"


class PressButtonGroup
{
public:
	void event_process(SDL_Event* event);

	//������� ������� � ������� ������ � � pressing �������� �����.
	void press(Button* button);

	void add(Button* button);

	//������� ������ buttons.
	void clear();

	std::vector<Button*> buttons;
	Button* pressing = nullptr;
};

