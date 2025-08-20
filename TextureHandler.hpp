#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <chrono>

class Object;


class TextureHandler
{
public:
	TextureHandler(Object* object);
	~TextureHandler();

	//num_anim - ����� ����
	//shot_of_anim - ���������� ������ � ��������
	//delay_ms - �������� ����� ������ ����� � ������������
	void start_anim(int num_anim = 0, int shot_of_anim = 1, int delay_ms = 50);

	//�������� ������������ ������� �����������.
	void change_show_rect(int column, int row);

	//��������.
	void process();

	// ��������� � ������������� ����������� �� ���������� ����.
	void set_texture(std::string file_name, float frame_w, float frame_h);

	//���������� ������ ����������� ��� ������ �������.
	void set_object_size();

protected:
	Object* object = nullptr;
	std::chrono::steady_clock::time_point anim_start;
	std::chrono::microseconds delay;
	int shot_of_anim;
	int shot_num = 0;
	bool is_plaing = false;

	SDL_Texture* texture = nullptr;
	SDL_FRect show_texture_frame;
	SDL_FRect size_texture_frame;
};

