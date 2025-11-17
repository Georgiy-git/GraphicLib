#pragma once

#include "Panel.hpp"
#include "Line.hpp"
#include <chrono>

class LineEdit : public Panel
{
public:
	LineEdit(
		SDL_Renderer* render,
		size_t max,
		float multiplier = 0.3,
		float corner_x = 0,
		float corner_y = 0,
		float object_distance = 3,
		float distance_of_border_w = 10,
		float distance_of_border_h = 5,
		rgb background_color = {255, 255, 255}
	);

	void process_event(SDL_Event* event) override;

	void iterate() override;

	void set_form(const object_form& form, bool default_values = true) override;

	void set_background_color(rgb color);

	bool has_focus();

	// Установить текст, стерев старый.
	void set_text(const std::string text);

	// Добавить текст к уже существующему.
	void append_text(const std::string text);

	// Получить текст строки.
	const std::string& get_text();

	// Установить шрифт для всех строк.
	static void set_font(SDL_Texture* font);

	// Установить шрифт по умолчанию.
	// Возвращает указатель на этот шрифт, вызывающий код отвечает
	// за освобождение памяти при необходимости.
	static SDL_Texture* set_default_font(SDL_Renderer* render);

	// Установить специальный шрифт для этой строки.
	void set_special_font(SDL_Texture* font);

	// Размер текста.
	const float& get_multiplier();

	// Удалить символ строки по индексу.
	void remove(int index) override;

	// Удалить последний символ строки.
	void pop_back() override;

	void clear() override;

	// Ширина символа.
	int get_symbol_w();

	// Высота символа.
	int get_symbol_h();

	void adjust_cursor();

private:
	bool inside(float x, float y) const override;

	Line line;
	Line cursor;

	size_t max;
	bool focus = false; // фокус ввода
	bool focus_flag = true; // для чередования горит/не горит курсор
	SDL_FRect frame;
	rgb background_color;
	std::chrono::steady_clock::time_point tp;
	std::chrono::milliseconds delay;
};

