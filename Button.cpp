#include "Button.hpp"

Button::Button(
	SDL_Renderer* render, 
	float center_x, 
	float center_y, 
	float width, 
	float height
)
	: Object(render, center_x, center_y, width, height)
{

}

void Button::process_event(SDL_Event* event)
{
	Object::process_event(event);

	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		if (in() && !pressing) change_show_rect(1, 0);
		else if (out() && !pressing) change_show_rect(0, 0);
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (cursor_inside()) {
			if (!pressing && flag_pressing) set_pressing();
			else if (pressing) remove_pressing();
			else change_show_rect(0, 0);
		}
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		if (cursor_inside()) change_show_rect(1, 0);
	}
}

void Button::remove_pressing() 
{
	pressing = false;
	change_show_rect(0, 0);
}

void Button::set_pressing() 
{
	pressing = true;
	change_show_rect(1, 0);
}

bool Button::get_pressing_flag() 
{
	return flag_pressing;
}

void Button::set_pressing_flag(bool flag) 
{
	flag_pressing = flag;
}

void Button::iterate()
{
	Object::iterate();
	/*if (line.has_value()) {
		line->iterate();
	}*/
}

//void Button::set_line(const std::string& line)
//{
//	this->line = std::make_optional<Line>(line, render);
//	this->line->set_x(get_form().corner_x + this->line->get_distance_of_border_w());
//	this->line->set_y(get_form().corner_y + this->line->get_distance_of_border_h());
//	set_width(this->line->get_distance_of_border_w() * 2 + this->line->get_form().width);
//	set_height(this->line->get_distance_of_border_h() * 2 + this->line->get_form().height);
//}
