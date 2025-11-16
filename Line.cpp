#include "Line.hpp"
#include "Font.hpp"

Line::Line(
	const std::string& line, 
	SDL_Renderer* render, 
	float multiplier, 
	float corner_x, 
	float corner_y,
	float object_distance, 
	float distance_of_border_w , 
	float distance_of_border_h
)
	: Panel(render, 'h', corner_x, corner_y, object_distance, distance_of_border_w, distance_of_border_h), 
	text{ text }, 
	multiplier(multiplier)
{
	set_text(line);
}

void Line::set_text(const std::string text)
{
	clear();
	append_text(text);
}

void Line::append_text(const std::string text)
{
	this->text += text;
	for (const auto& symbol : text) {
		auto symb = std::make_shared<Object>(render, 0, 0, symbol_w * multiplier, symbol_h * multiplier);
		if (special_font != nullptr) symb->set_texture(special_font, symbol_w, symbol_h);
		else symb->set_texture(font, symbol_w, symbol_h);
		std::pair pos = Font[symbol];
		int pos_x = pos.first;
		int pos_y = pos.second;
		symb->change_show_rect(pos_x, pos_y);
		add(symb);
	}
}

void Line::set_font(SDL_Texture* font) 
{
	Line::font = font;
}

SDL_Texture* Line::set_default_font(SDL_Renderer* render) 
{
	font = IMG_LoadTexture(render, "textures\\symbols.svg");
	return font;
}

void Line::set_special_font(SDL_Texture* font) 
{
	special_font = font;
}

const float& Line::get_multiplier()
{
	return multiplier;
}

void Line::remove(int index)
{
	Panel::remove(index);
	std::string _text;
	for (int i = 0; i < text.size(); ++i) {
		if (i != index) _text += text[i];
	}
	text = _text;
}

void Line::pop_back()
{
	if (objects_count() == 0) return;
	Panel::pop_back();
	text.pop_back();
}

void Line::clear()
{
	Panel::clear();
	text.clear();
}

const std::string& Line::get_text() 
{
	return text;
}
