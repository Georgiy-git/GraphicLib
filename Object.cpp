
#include "TextureHandler.hpp"
#include "Object.hpp"


Object::Object(SDL_Renderer* render, float center_x, float center_y, float width, float height)
	: render(render), form{ center_x, center_y, width, height },
	texture_handler{ std::make_shared<TextureHandler>(&form, render) }
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

const bool Object::in() {
	return in_flag;
}

const bool Object::out() {
	return out_flag;
}

const bool Object::inside() {
	return inside_flag;
}

const bool Object::inside(float x, float y) {
	return (x > form.left_border && x < form.right_border &&
		y > form.upper_border && y < form.lower_border);
}

void Object::set_render_draw_color(rgba _rgba) {
	SDL_SetRenderDrawColor(render, _rgba[0], _rgba[1], _rgba[2], _rgba[3]);
}

rgba Object::pack_uint8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return rgba{r, g, b, a};
}

void Object::set_texture(std::string file_name, float frame_w, float frame_h) {
	texture_handler->set_texture(file_name, frame_w, frame_h);
}

void Object::change_show_rect(int column, int row) {
	texture_handler->change_show_rect(column, row);
}

void Object::iterate() {
	texture_handler->process();
	render_frame_iter();
}

void Object::event_process(SDL_Event* event) {
	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		if (inside(event->button.x, event->button.y)) {
			if (!inside_flag) {
				inside_flag = true;
				in_flag = true;
			}
			else {
				if (in_flag) in_flag = false;
			}
		}
		else {
			if (inside_flag) {
				inside_flag = false;
				out_flag = true;
			}
			else {
				if (out_flag) out_flag = false;
			}
		}
	}
}

void Object::render_frame_iter()
{
	if (flag_render_frame) {
		set_render_draw_color(frame_color);
		SDL_RenderRect(render, &frame);
	}
}

void Object::set_frame_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	frame_color = pack_uint8(r, g, b, a); 
}

void Object::set_frame_size(float x)
{
	multiplier = x;
	frame.x = form.left_border - (form.right_border - form.left_border) * (x - 1) / 2;
	frame.y = form.upper_border - (form.lower_border - form.upper_border) * (x - 1) / 2;
	frame.w = (form.right_border - form.left_border) * x;
	frame.h = (form.lower_border - form.upper_border) * x;
}

void Object::add_x(float x) {
	set_form({ form.corner_x + x , form.corner_y, form.width, form.height });
}

void Object::add_y(float y) {
	set_form({ form.corner_x, form.corner_y + y, form.width, form.height });
}

void Object::render_frame(bool flag) {
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

	texture_handler->set_object_size();
	set_frame_size(multiplier);
}

const object_form& Object::get_form() {
	return form;
}

void Object::start_anim(int num_anim, int shot_of_anim, int delay_ms) {
	texture_handler->start_anim(num_anim, shot_of_anim, delay_ms);
}
