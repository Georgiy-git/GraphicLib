#include "LineEdit.hpp"
#include "Keyboard.hpp"

//LineEdit::LineEdit(
//	SDL_Renderer* render,
//	size_t max,
//	float multiplier,
//	float corner_x,
//	float corner_y,
//	float object_distance,
//	float distance_of_border_w,
//	float distance_of_border_h,
//	rgb background_color
//)
//	: Panel(render, 'h', corner_x, corner_y, object_distance, 0, 0),
//	line("", 
//		render, 
//		multiplier, 
//		corner_x, 
//		corner_y, 
//		object_distance, 
//		distance_of_border_w, 
//		distance_of_border_h
//	),
//	cursor("", render, multiplier, corner_x, corner_y, 0, 0, 0),
//	background_color{ background_color }, 
//	delay(500), 
//	tp(std::chrono::steady_clock::now() - delay), 
//	max{ max }
//{
//	frame = {
//		corner_x,
//		corner_y,
//		line.get_symbol_w() * line.get_multiplier() * max + line.get_distance() * (max - 1) +
//		line.get_distance_of_border_w() * 2,
//		float(line.get_symbol_h() * line.get_multiplier()) + line.get_distance_of_border_h() * 2
//	};
//}

LineEdit::LineEdit(SDL_Renderer* renderer, size_t max, float x, float y)
	: Panel(renderer, x, y), line("", renderer), cursor("", renderer)
{
}

LineEdit::LineEdit(SDL_Renderer* renderer, size_t max)
	: Panel(renderer), line("", renderer), cursor("", renderer)
{
}

void LineEdit::process(SDL_Event* event)
{
	Panel::process(event);
	if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (cursor_inside()) {
			focus = true;
		}
		else {
			focus = false;
		}
	}
	else if (event->type == SDL_EVENT_KEY_DOWN) {
		if (focus) {
			if (event->key.scancode == SDL_SCANCODE_BACKSPACE) {
				pop_back();
			} 
			else if (event->key.scancode == SDL_SCANCODE_RETURN) {
				focus = !focus;
			}
			else if (line.size() < max) {
				std::string text;
				text += get_char(event);
				append_text(text);
			}
		}
	}
}

void LineEdit::iterate()
{
	SDL_SetRenderDrawColor(renderer, background_color[0], background_color[1], background_color[2], 255);
	SDL_RenderFillRect(renderer, &frame);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderRect(renderer, &frame);
	Panel::iterate();
	if (focus) {
		if (std::chrono::steady_clock::now() - tp > delay) {
			tp = std::chrono::steady_clock::now();
			if (focus_flag) {
				cursor.append_text("|");
			}
			else {
				cursor.pop_back();
			}
			focus_flag = !focus_flag;
		}
	}
	else if (!focus && !focus_flag) {
		cursor.pop_back();
		focus_flag = !focus_flag;
	}
	line.iterate();
	//cursor.iterate();
}

//void LineEdit::set_form(const object_form& form, bool default_values)
//{
//	Panel::set_form(form, default_values);
//	if (form.corner_x != 0) {
//		frame.x = form.corner_x;
//		line.set_x(form.corner_x);
//	}
//	if (form.corner_y != 0) {
//		float y = form.corner_y - float(line.get_symbol_h() * line.get_multiplier() * 0.2);
//		frame.y = y;
//		line.set_y(y);
//	}
//	adjust_cursor();
//}

void LineEdit::set_background_color(rgb color)
{
	background_color = color;
}

bool LineEdit::has_focus()
{
	return focus;
}

bool LineEdit::inside(float x, float y) const
{
	return (x > frame.x && x < frame.x + frame.w &&
		y > frame.y && y < frame.y + frame.h);
}

void LineEdit::set_text(const std::string text) 
{
	line.set_text(text);
	adjust_cursor();
	
}

void LineEdit::append_text(const std::string text) 
{
	line.append_text(text);
	adjust_cursor();
}

const std::string& LineEdit::get_text()
{
	return line.get_text();
}

void LineEdit::set_font(SDL_Texture* font) 
{
	Line::set_font(font);
}

SDL_Texture* LineEdit::set_default_font(SDL_Renderer* render)
{
	return Line::set_default_font(render);
}

void LineEdit::set_special_font(SDL_Texture* font)
{
	line.set_special_font(font);
	cursor.set_special_font(font);
}

const float& LineEdit::get_multiplier()
{
	return line.get_multiplier();
}

void LineEdit::remove(int index)
{
	line.remove(index);
	adjust_cursor();
}

void LineEdit::pop_back()
{
	line.pop_back();
	adjust_cursor();
}

void LineEdit::clear()
{
	line.clear();
	adjust_cursor();
}

int LineEdit::get_symbol_w()
{
	return line.get_symbol_w();
}

int LineEdit::get_symbol_h()
{
	return line.get_symbol_h();
}

void LineEdit::adjust_cursor()
{
	/*cursor.set_x(line.get_form().corner_x + line.size() * line.get_symbol_w() * line.get_multiplier() + 
		line.get_distance() * (line.size() - (size() > 1 ? 1 : 0)) + line.get_distance_of_border_w());
	cursor.set_y(line.get_form().corner_y + line.get_distance_of_border_h());*/
}
