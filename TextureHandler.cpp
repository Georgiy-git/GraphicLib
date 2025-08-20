
#include "TextureHandler.hpp"


TextureHandler::TextureHandler(object_form* form, SDL_Renderer* render)
	: form{ form }, render{render} {
}

TextureHandler::~TextureHandler()
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void TextureHandler::start_anim(int num_anim, int shot_of_anim, int delay_ms)
{
	is_plaing = true;
	show_texture_frame.x = 0;
	show_texture_frame.y = num_anim * show_texture_frame.h;
	shot_num = 0;
	this->shot_of_anim = shot_of_anim;
	delay = std::chrono::milliseconds(delay_ms);
}

void TextureHandler::change_show_rect(int column, int row)
{
	show_texture_frame.x = show_texture_frame.w * column;
	show_texture_frame.y = show_texture_frame.h * row;
}

void TextureHandler::process()
{
	if (texture == nullptr) return;

	if (is_plaing) {
		if (std::chrono::steady_clock::now() - anim_start > delay) {
			if (shot_num < shot_of_anim) {
				show_texture_frame.x += show_texture_frame.w;
				shot_num++;
				anim_start = std::chrono::steady_clock::now();
			}
			else {
				is_plaing = false;
				shot_num = 0;
			}
		}
	}

	SDL_RenderTexture(render, texture, 
		&show_texture_frame, &size_texture_frame);
}


void TextureHandler::set_texture(std::string file_name, float frame_w, float frame_h)
{
	texture = IMG_LoadTexture(render, file_name.c_str());
	set_object_size();
	show_texture_frame.x = 0;
	show_texture_frame.y = 0;
	show_texture_frame.w = frame_w;
	show_texture_frame.h = frame_h;
}

void TextureHandler::set_object_size()
{
	size_texture_frame.x = form->center_x;
	size_texture_frame.y = form->center_y;
	size_texture_frame.w = form->width;
	size_texture_frame.h = form->height;
}
