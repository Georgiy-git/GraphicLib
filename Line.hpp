#pragma once

#include "Panel.hpp"


/* Текстовая строка.
* Для отображения установите шрифт.
*/

class Line : public Panel
{
public:
	Line(const std::string& line, SDL_Renderer* render, float corner_x, float corner_y,
		float multiplier = 1,
		float distance = 5, float distance_of_border_w = 20, float distance_of_border_h = 20);

	void event_process(SDL_Event* event) override;

	// Установить текст, стерев старый.
	void set_text(const std::string& text);

	// Добавить текст к уже существующему.
	void append_text(const std::string& text);

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

private:
	static inline SDL_Texture* font;

	SDL_Texture* special_font = nullptr;

	float multiplier;
	std::string line;
	int symbol_w = 60;
	int symbol_h = 100;
};

