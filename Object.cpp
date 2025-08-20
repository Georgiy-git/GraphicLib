
#include "TextureHandler.hpp"
#include "Object.hpp"


Object::Object(SDL_Renderer* render, float center_x, float center_y, float width, float height)
	: render(render), center_x(center_x), center_y(center_y), width(width), height(height),
	texture_handler{ std::make_shared<TextureHandler>(this) }
{
	set_size(-1, -1, -1, -1);
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
	return (x > left_border && x < right_border &&
		y > upper_border && y < lower_border);
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
	frame.x = left_border - (right_border - left_border) * (x - 1) / 2;
	frame.y = upper_border - (lower_border - upper_border) * (x - 1) / 2;
	frame.w = (right_border - left_border) * x;
	frame.h = (lower_border - upper_border) * x;
}

void Object::render_frame(bool flag) {
	flag_render_frame = flag;
}

void Object::set_size(float center_x, float center_y, float width, float height)
{
	if (center_x != -1) { this->center_x = center_x; }
	if (center_y != -1) { this->center_y = center_y; }
	if (width != -1)	{ this->width = width; }
	if (height != -1) { this->height = height; }

	left_border = this->center_x;
	right_border = this->center_x + this->width;
	upper_border = this->center_y;
	lower_border = this->center_y + this->height;

	texture_handler->set_object_size();
	set_frame_size(multiplier);
}

void Object::start_anim(int num_anim, int shot_of_anim, int delay_ms) {
	texture_handler->start_anim(num_anim, shot_of_anim, delay_ms);
}
