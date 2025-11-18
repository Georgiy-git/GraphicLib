#pragma once

#include "Panel.hpp"


/* Текстовая строка.
* Для отображения установите шрифт.
*/

class Line : public Panel
{
public:
	Line(const std::string line, SDL_Renderer* renderer, float x, float y);
	Line(const std::string line, SDL_Renderer* renderer);

	void set_text(const std::string text);

	void append_text(const std::string text);

	const std::string& get_text();

	static void set_font(SDL_Texture* font);

	static SDL_Texture* set_default_font(SDL_Renderer* renderer);

	void set_special_font(SDL_Texture* font);

	const float& get_multiplier();

	void set_multiplier(float multiplier);

	void remove(int index) override;

	void pop_back() override;

	void clear() override;

	int get_symbol_w();

	int get_symbol_h();

protected:
	std::string text;

	static inline SDL_Texture* font;

	SDL_Texture* special_font = nullptr;

	float multiplier = 0.3;
	int symbol_w = 60;
	int symbol_h = 100;
};

