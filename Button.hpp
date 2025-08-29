#pragma once

#include "Object.hpp";

/*
“ребование к текстуре: соотношение 1 высота к 2 ширина,
одна текстура из двух составл€ющих:
слева кнопка до нажати€, справа - после нажати€.
*/

class Button : public Object
{
public:
	Button(SDL_Renderer* render, float center_x, float center_y, float width, float height);

	void event_process(SDL_Event* event) override;

	// ”становить зажатие.
	void remove_pressing();

	//—н€ть зажатие.
	void set_pressing();

	// true, если включена функци€€ зажати€.
	bool get_pressing_flag();

	// ѕереключить опцию зажати€.
	void set_pressing_flag(bool flag);
	
private:
	bool pressing = false;
	bool flag_pressing = false;
};

