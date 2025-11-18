#include "TextureHandler.hpp"
#include "Object.hpp"


Object::Object(SDL_Renderer* renderer, float x, float y, float width, float height)
	: renderer(renderer), x{x}, y{y}, width{width}, height{height},
	texture_handler(renderer, this->x, this->y, this->width, this->height)
{
	adjust();
}

Object::Object(SDL_Renderer* renderer, float width, float height)
	: renderer(renderer), width{width}, height{height},
	texture_handler(renderer, this->x, this->y, this->width, this->height)
{
	adjust();
}

Object::Object(SDL_Renderer* renderer)
	: renderer(renderer),
	texture_handler(renderer, this->x, this->y, this->width, this->height)
{
	adjust();
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
	return (x > left_border && x < right_border &&
		y > upper_border && y < lower_border);
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

void Object::process(SDL_Event* event) 
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
		SDL_SetRenderDrawColor(renderer, frame_color[0], frame_color[1], frame_color[2], 255);
		SDL_RenderRect(renderer, &frame);
	}
}

void Object::set_frame_color(uint8_t r, uint8_t g, uint8_t b) 
{
	frame_color = { r, g, b };
}

void Object::set_frame_multiplier(float x)
{
	multiplier = x;
	adjust_frame();
}

void Object::change(
	std::optional<float> x, 
	std::optional<float> y, 
	std::optional<float> width, 
	std::optional<float> height)
{
	if (x.has_value()) this->x = x.value();
	if (y.has_value()) this->y = y.value();
	if (width.has_value()) this->width = width.value();
	if (height.has_value()) this->height = height.value();

	adjust();
}

void Object::adjust()
{
	left_border = x;
	right_border = x + width;
	upper_border = y;
	lower_border = y + height;

	texture_handler.adjust();
	adjust_frame();
}

void Object::adjust_frame()
{
	frame.x = left_border - width * (multiplier - 1) / 2;
	frame.y = upper_border - height * (multiplier - 1) / 2;
	frame.w = width * multiplier;
	frame.h = height * multiplier;
}

void Object::add_x(float x) 
{
	change(this->x + x, std::nullopt, std::nullopt, std::nullopt);
}

void Object::add_y(float y) 
{
	change(std::nullopt, this->y + y, std::nullopt, std::nullopt);
}

void Object::set_x(float x)
{
	change(x, std::nullopt, std::nullopt, std::nullopt);
}

void Object::set_y(float y)
{
	change(std::nullopt, y, std::nullopt, std::nullopt);
}

float Object::get_x()
{
	return x;
}

float Object::get_y()
{
	return y;
}

void Object::render_frame(bool flag) 
{
	flag_render_frame = flag;
}

void Object::set_width(float width)
{
	this->width = width;
	adjust();
}

void Object::set_height(float height)
{
	this->height = height;
	adjust();
}

float Object::get_width()
{
	return width;
}

float Object::get_height()
{
	return height;
}

void Object::start_animation(int num, int shot, int delay_ms) 
{
	texture_handler.start_animation(num, shot, delay_ms);
}
