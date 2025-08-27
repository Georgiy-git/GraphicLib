#include "Line.hpp"
#include "Font.hpp"

Line::Line(const std::string& line, SDL_Renderer* render, float corner_x, float corner_y, float multiplier,
	float distance, float distance_of_border_w, float distance_of_border_h)
	: Panel(render, corner_x, corner_y, 0, 0, 'h', distance, distance_of_border_w, distance_of_border_h),
	line{ line }, multiplier(multiplier)
{
	font = IMG_LoadTexture(render, "textures\\symbols.svg");
	set_text(line);
}

void Line::event_process(SDL_Event* event)
{

}

void Line::set_text(const std::string& text)
{
	for (const auto& symbol : text) {
		auto symb = std::make_shared<Object>(render, 0, 0, symbol_w * multiplier, symbol_h * multiplier);
		symb->set_texture(font, symbol_w, symbol_h);
		std::pair pos = Font[symbol];
		int pos_x = pos.first;
		int pos_y = pos.second;
		symb->change_show_rect(pos_x, pos_y);
		add(symb);
	}
}

void Line::set_font(const std::string& file_name) {

}

const std::string& Line::get_text() {
	return line;
}
