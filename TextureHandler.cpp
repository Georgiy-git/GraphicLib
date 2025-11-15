#include "TextureHandler.hpp"
#include "Object.hpp"

TextureHandler::TextureHandler(object_form* form, SDL_Renderer* render)
	: form{ form }, render{render} 
{

}

void TextureHandler::start_animation(int num, int shot, int delay_ms)
{
	is_playing = true;
	show_rect.x = 0;
	show_rect.y = num * show_rect.h;
	this->shot_num = 0;
	this->shot_of_anim = shot - 1;
	delay = std::chrono::milliseconds(delay_ms);
}

void TextureHandler::change_show_rect(int column, int row)
{
	show_rect.x = show_rect.w * column;
	show_rect.y = show_rect.h * row;
}

void TextureHandler::iterate()
{
	if (texture == nullptr) return;

	if (is_playing) {
		if (std::chrono::steady_clock::now() - animation_start > delay) {
			if (shot_num < shot_of_anim) {
				show_rect.x += show_rect.w;
				shot_num++;
				animation_start = std::chrono::steady_clock::now();
			}
			else {
				is_playing = false;
				shot_num = 0;
			}
		}
	}

	SDL_RenderTexture(render, texture, 
		&show_rect, &size_rect);
}

void TextureHandler::set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_px)
{
	this->texture = texture;
	set_object_size();
	show_rect.x = 0;
	show_rect.y = 0;
	show_rect.w = (float)frame_w_px;
	show_rect.h = (float)frame_h_px;
}

void TextureHandler::set_object_size()
{
	size_rect.x = form->corner_x;
	size_rect.y = form->corner_y;
	size_rect.w = form->width;
	size_rect.h = form->height;
}
