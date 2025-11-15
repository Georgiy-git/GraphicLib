#include "LineEdit.hpp"
#include "Keyboard.hpp"

LineEdit::LineEdit(
	SDL_Renderer* render,
	size_t max,
	float multiplier,
	float corner_x,
	float corner_y,
	float object_distance,
	float distance_of_border_w,
	float distance_of_border_h,
	rgb background_color
)
	: Line(
		"",
		render,
		multiplier,
		corner_x,
		corner_y,
		object_distance, 
		distance_of_border_w,
		distance_of_border_h
	),
	background_color{ background_color }, 
	delay(500), 
	tp(std::chrono::steady_clock::now() - delay), 
	max{ max }
{
	frame = { 
		corner_x, 
		corner_y,
		symbol_w * multiplier * max + object_distance * (max - 1) + distance_of_border_w * 2, 
		float(symbol_h * multiplier * 1.4) 
	};
}

void LineEdit::process_event(SDL_Event* event)
{
	Line::process_event(event);
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
				if (!focus_flag) {
					pop_back();
					append_text("|");
				}
			} 
			else if (event->key.scancode == SDL_SCANCODE_RETURN) {
				focus = !focus;
				if (!focus_flag) {
					pop_back();
					focus_flag = !focus_flag;
				}
				std::cout << get_text();
			}
			else if (objects_count() < max) {
				std::string text;
				text += get_char(event);
				if (!focus_flag) {
					pop_back();
					text += '|';
				}
				append_text(text);
			}
		}
	}
}

void LineEdit::iterate()
{
	SDL_SetRenderDrawColor(render, background_color[0], background_color[1], background_color[2], 255);
	SDL_RenderFillRect(render, &frame);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderRect(render, &frame);
	Line::iterate();
	if (focus) {
		if (std::chrono::steady_clock::now() - tp > delay) {
			tp = std::chrono::steady_clock::now();
			if (focus_flag) {
				append_text("|");
			}
			else {
				pop_back();
			}
			focus_flag = !focus_flag;
		}
	}
	else if (!focus && !focus_flag) {
		pop_back();
		focus_flag = !focus_flag;
	}
}

void LineEdit::set_form(const object_form& form, bool default_values)
{
	Line::set_form(form, default_values);
	if (form.corner_x != 0 ) frame.x = form.corner_x;
	if (form.corner_y != 0)frame.y = form.corner_y - float(symbol_h * multiplier * 0.2);
}

void LineEdit::set_background_color(rgb color)
{
	background_color = color;
}

bool LineEdit::inside(float x, float y) const
{
	return (x > frame.x && x < frame.x + frame.w &&
		y > frame.y && y < frame.y + frame.h);
}
