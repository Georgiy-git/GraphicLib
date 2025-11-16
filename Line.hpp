#pragma once

#include "Panel.hpp"


/* Текстовая строка.
* Для отображения установите шрифт.
*/

class Line : public Panel
{
public:
	Line(
		const std::string& line, 
		SDL_Renderer* render, 
		float multiplier = 0.3, 
		float corner_x = 0, 
		float corner_y = 0, 
		float object_distance = 3,
		float distance_of_border_w = 0, 
		float distance_of_border_h = 0
	);

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

protected:
	std::string text;

	static inline SDL_Texture* font;

	SDL_Texture* special_font = nullptr;

	float multiplier = 0.5;
	int symbol_w = 60;
	int symbol_h = 100;
};

