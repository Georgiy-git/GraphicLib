#pragma once

#include "Panel.hpp"


/* Текстовая строка
*/

class Line : public Panel
{
public:
	Line(const std::string& line, SDL_Renderer* render, float corner_x, float corner_y,
		float multiplier = 1,
		float distance = 5, float distance_of_border_w = 20, float distance_of_border_h = 20);

	virtual void event_process(SDL_Event* event) override;

	virtual ~Line() override = default;

	void set_text(const std::string& text);

	void add_text(const std::string& text);

	const std::string& get_text();

	void set_font(const std::string& file_name);

private:
	float multiplier;
	SDL_Texture* font;
	std::string line;
	int symbol_w = 60;
	int symbol_h = 100;
};

