#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <chrono>
#include "Object.hpp"


class TextureHandler
{
public:
	TextureHandler(object_form* form, SDL_Renderer* render);
	~TextureHandler();

	//num_anim - ����� ����
	//shot_of_anim - ���������� ������ � ��������
	//delay_ms - �������� ����� ������ ����� � ������������
	void start_anim(int num_anim = 0, int shot_of_anim = 1, int delay_ms = 50);

	//�������� ������������ ������� �����������.
	void change_show_rect(int column, int row);

	//��������.
	void process();

	// ������������� ����������� �����������.
	void set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_px);

	//���������� ������ ����������� ��� ������ �������.
	void set_object_size();

protected:
	object_form* form;
	SDL_Renderer* render;

	std::chrono::steady_clock::time_point anim_start;
	std::chrono::microseconds delay;
	int shot_of_anim = 0;
	int shot_num = 0;
	bool is_plaing = false;

	SDL_Texture* texture = nullptr;
	SDL_FRect show_texture_frame;
	SDL_FRect size_texture_frame;
};

