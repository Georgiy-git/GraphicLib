#pragma once

#include <optional>

#include "Object.hpp";
#include "Line.hpp";

/*
Требование к текстуре: соотношение 1 высота к 2 ширина,
одна текстура из двух составляющих: слева кнопка до нажатия, справа - после нажатия.
*/

class Button : public Object
{
	friend class PressButtonGroup;

public:
	using Object::Object;
	void process(SDL_Event* event) override;
	void iterate() override;

	bool pressed();

	// true, если включена функция зажатия.
	bool get_pressing_flag();

	// Переключить опцию зажатия.
	void set_pressing_flag(bool flag);

	// Установить надпись поверх кнопки.
	//void set_line(const std::string& line);

	// Надпись поверх кнопки.
	std::optional<Line> line;
	
private:
	//Снять зажатие.
	void remove_pressing();

	// Установить зажатие.
	void set_pressing();

	bool pressing = false;
	bool flag_pressing = false;
};

