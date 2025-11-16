#pragma once

#include "Line.hpp"
#include <chrono>

class LineEdit : public Line
{
public:
	LineEdit(
		SDL_Renderer* render,
		size_t max,
		float multiplier = 0.3,
		float corner_x = 0,
		float corner_y = 0,
		float object_distance = 3,
		float distance_of_border_w = 0,
		float distance_of_border_h = 0,
		rgb background_color = {255, 255, 255}
	);

	void process_event(SDL_Event* event) override;

	void iterate() override;

	void set_form(const object_form& form, bool default_values = true) override;

	void set_background_color(rgb color);

	bool has_focus();

private:
	bool inside(float x, float y) const override;

	size_t max;
	bool focus = false; // фокус ввода
	bool focus_flag = true; // дл€ чередовани€ горит/не горит курсор
	SDL_FRect frame;
	rgb background_color;
	std::chrono::steady_clock::time_point tp;
	std::chrono::milliseconds delay;
};

