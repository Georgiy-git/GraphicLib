#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <memory>
#include <iostream>


using rgba = std::array<uint8_t, 4>;

class Object //������� ����� ��� ���� ����������� ��������.
{
	friend class TextureHandler;

public:
	//�������������� init, iter, event � quit.
	Object(SDL_Renderer* render, float center_x, float center_y, float width, float height);
	virtual void iterate();
	virtual void event_process(SDL_Event* event);
	virtual ~Object();

	//���������� ������ ������.
	static std::pair<int, int> get_display_size();

	// ��������� � ������������� ����������� �� ���������� ����.
	void set_texture(std::string file_name, float frame_w, float frame_h);

	//��������� ������������� �����.
	void change_show_rect(int column, int row);

	//��������� ����� ���������� �����.
	void set_frame_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//����� ������ ����� ��������� x.
	void set_frame_size(float x = 1);

	//���������� ���������� �����.
	void render_frame(bool flag);

	//��� -1 �������� ��������������� ����� ������������ �������.
	//center_x � center_y - ���������� �������� ������ ���� �������.
	void set_size(float center_x = -1, float center_y = -1, float width = -1, float height = -1);

	//�������� ��������� �������� �������.
	float center_x, center_y, width, height,
		left_border, right_border, upper_border, lower_border;

	//���� ������� ���� � ������� �������.
	const bool in();

	//����� ������� ���� �� ������� �������.
	const bool out();

	//���������� true, ���� ������ ������ ������� �������.
	const bool inside();

	//num_anim - ����� ����
	//shot_of_anim - ���������� ������ � ��������
	//delay_ms - �������� ����� ������ ����� � ������������
	void start_anim(int num_anim = 0, int shot_of_anim = 1, int delay_ms = 50);

protected:
	virtual const bool inside(float x, float y);

	void set_render_draw_color(rgba _rgba);
	static rgba pack_uint8(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

private:
	bool inside_flag = false;
	bool in_flag = false;
	bool out_flag = false;

	SDL_Renderer* render = nullptr;

	std::shared_ptr<TextureHandler> texture_handler = nullptr;

	void render_frame_iter();
	bool flag_render_frame = false;
	rgba frame_color = { 0, 255, 0, 255 };
	float multiplier;
	SDL_FRect frame;
};

/*   ����������

��� ����������� ����������� ������� ������������ set_size, 
��� ��� ��� ������������� �������������� ������� �������.

����������� ����������� ������� �������������� ������ � ������� ��������.
*/