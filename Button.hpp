#pragma once

#include <optional>

#include "Object.hpp";
#include "Line.hpp";

/*
Требование к текстуре: соотношение 1 высота к 2 ширина,
одна текстура из двух составляющих:
слева кнопка до нажатия, справа - после нажатия.
*/

class Button : public Object
{
public:
	Button(
		SDL_Renderer* render, 
		float corner_x, 
		float corner_y, 
		float width, 
		float height
	);

	void process_event(SDL_Event* event) override;

	// Установить зажатие.
	void remove_pressing();

	//Снять зажатие.
	void set_pressing();

	// true, если включена функция зажатия.
	bool get_pressing_flag();

	// Переключить опцию зажатия.
	void set_pressing_flag(bool flag);

	void iterate() override;

	// Установить надпись поверх кнопки.
	void set_line(const std::string& line);

	// Надпись поверх кнопки.
	std::optional<Line> line;
	
private:
	bool pressing = false;
	bool flag_pressing = false;
};

