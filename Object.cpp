#include "TextureHandler.hpp"
#include "Object.hpp"


Object::Object(SDL_Renderer* render, float center_x, float center_y, float width, float height)
	: render(render), form{ center_x, center_y, width, height },
	texture_handler(&form, render)
{
	set_form({});
	set_frame_size();
}

Object::~Object() {	}

std::pair<int, int> Object::get_display_size()
{
	SDL_Rect display_bounds;
	SDL_DisplayID id = SDL_GetPrimaryDisplay();
	SDL_GetDisplayBounds(id, &display_bounds);
	return std::pair<int, int>(display_bounds.w, display_bounds.h);
}

bool Object::in() const {
	return in_flag;
}

bool Object::out() const {
	return out_flag;
}

bool Object::cursor_inside() const {
	return inside_flag;
}

bool Object::inside(float x, float y) const {
	return (x > form.left_border && x < form.right_border &&
		y > form.upper_border && y < form.lower_border);
}

void Object::set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_px) 
{
	texture_handler.set_texture(texture, frame_w_px, frame_h_px);
}

void Object::change_show_rect(int column, int row) 
{
	texture_handler.change_show_rect(column, row);
}

void Object::iterate() 
{
	texture_handler.iterate();
	iterate_frame();
}

void Object::process_event(SDL_Event* event) 
{
	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		if (in_flag) in_flag = false;
		if (out_flag) out_flag = false;

		if (inside(event->button.x, event->button.y)) {
			if (!inside_flag) {
				inside_flag = true;
				in_flag = true;
			}
		}
		else {
			if (inside_flag) {
				inside_flag = false;
				out_flag = true;
			}
		}
	}
}

void Object::iterate_frame()
{
	if (flag_render_frame) {
		SDL_SetRenderDrawColor(render, frame_color[0], frame_color[1], frame_color[2], 255);
		SDL_RenderRect(render, &frame);
	}
}

void Object::set_frame_color(uint8_t r, uint8_t g, uint8_t b) 
{
	frame_color = { r, g, b };
}

void Object::set_frame_size(float x)
{
	multiplier = x;
	frame.x = form.left_border - (form.right_border - form.left_border) * (x - 1) / 2;
	frame.y = form.upper_border - (form.lower_border - form.upper_border) * (x - 1) / 2;
	frame.w = (form.right_border - form.left_border) * x;
	frame.h = (form.lower_border - form.upper_border) * x;
}

void Object::add_x(float x) 
{
	set_form({ form.corner_x + x , form.corner_y, form.width, form.height });
}

void Object::add_y(float y) 
{
	set_form({ form.corner_x, form.corner_y + y, form.width, form.height });
}

void Object::set_x(float x)
{
	set_form({ .corner_x = x });
}

void Object::set_y(float y)
{
	set_form({ .corner_y = y });
}

void Object::set_width(float width)
{
	set_form({ .width = width });
}

void Object::set_height(float height)
{
	set_form({ .height = height });
}

void Object::render_frame(bool flag) 
{
	flag_render_frame = flag;
}

void Object::set_form(const object_form& form, bool default_values)
{
	if (default_values) {
		if (form.corner_x) { this->form.corner_x = form.corner_x; }
		if (form.corner_y) { this->form.corner_y = form.corner_y; }
		if (form.width) { this->form.width = form.width; }
		if (form.height) { this->form.height = form.height; }
	}
	else {
		this->form.corner_x = form.corner_x;
		this->form.corner_y = form.corner_y;
		this->form.width = form.width;
		this->form.height = form.height;
	}

	this->form.left_border = this->form.corner_x;
	this->form.right_border = this->form.corner_x + this->form.width;
	this->form.upper_border = this->form.corner_y;
	this->form.lower_border = this->form.corner_y + this->form.height;

	texture_handler.set_object_size();
	set_frame_size(multiplier);
}

const object_form& Object::get_form() const 
{
	return form;
}

void Object::start_animation(int num, int shot, int delay_ms) 
{
	texture_handler.start_animation(num, shot, delay_ms);
}
