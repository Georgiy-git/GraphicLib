#pragma once

#include "Panel.hpp"
#include "Line.hpp"
#include <chrono>

class LineEdit : public Panel
{
public:
	LineEdit(SDL_Renderer* renderer, size_t max, float x, float y);
	LineEdit(SDL_Renderer* renderer, size_t max);

	void process(SDL_Event* event) override;

	void iterate() override;

	void set_background_color(rgb color);

	bool has_focus();

	void set_text(const std::string text);

	void append_text(const std::string text);

	const std::string& get_text();

	static void set_font(SDL_Texture* font);

	static SDL_Texture* set_default_font(SDL_Renderer* renderer);

	void set_special_font(SDL_Texture* font);

	const float& get_multiplier();

	void remove(int index) override;

	void pop_back() override;

	void clear() override;

	int get_symbol_w();
	int get_symbol_h();

	void adjust_cursor();

private:
	bool inside(float x, float y) const override;

	Line line;
	Line cursor;

	size_t max;
	bool focus = false; // фокус ввода
	bool focus_flag = true; // дл€ чередовани€ горит/не горит курсор
	SDL_FRect frame;
	rgb background_color;
	std::chrono::steady_clock::time_point tp;
	std::chrono::milliseconds delay;
};

