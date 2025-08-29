#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <memory>
#include <iostream>


using rgba = std::array<uint8_t, 4>;

typedef struct {
	float
	corner_x,
	corner_y,
	width,
	height,
	left_border,
	right_border,
	upper_border,
	lower_border;
} object_form;


class Object //������� ����� ��� ���� ����������� ��������.
{
	friend class TextureHandler;

public:
	//�������������� init, iter, event � quit.
	Object(SDL_Renderer* render, float corner_x, float corner_y, float width, float height);
	virtual void iterate();
	virtual void event_process(SDL_Event* event);
	virtual ~Object();

	//���������� ������ ������.
	static std::pair<int, int> get_display_size();

	// ������������� ����������� �����������.
	void set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_py);

	//��������� ������������� �����.
	void change_show_rect(int column, int row);

	//��������� ����� ���������� �����.
	void set_frame_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	//����� ������ ����� ��������� x.
	void set_frame_size(float x = 1);

	//��������� � � ������� ���������� �� �����������.
	void add_x(float x);

	//��������� � � ������� ���������� �� ���������.
	void add_y(float y);

	//���������� ���������� �����.
	void render_frame(bool flag);

	//��� default_values = true ������� �������� ���������� ��������� ����������� �� �����.
	void set_form(const object_form& form, bool default_values = true);

	const object_form& get_form() const;

	//���� ������� ���� � ������� �������.
	bool in() const;

	//����� ������� ���� �� ������� �������.
	bool out() const;

	//���������� true, ���� ������ ������ ������� �������.
	bool inside() const;

	//num_anim - ����� ����
	//shot_of_anim - ���������� ������ � ��������
	//delay_ms - �������� ����� ������ ����� � ������������
	void start_anim(int num_anim = 0, int shot_of_anim = 1, int delay_ms = 50);

protected:
	object_form form;

	virtual bool inside(float x, float y) const;

	void set_render_draw_color(rgba _rgba);
	static rgba pack_uint8(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	SDL_Renderer* render = nullptr;

private:
	bool inside_flag = false;
	bool in_flag = false;
	bool out_flag = false;

	std::shared_ptr<TextureHandler> texture_handler = nullptr;

	void render_frame_iter();
	bool flag_render_frame = false;
	rgba frame_color = { 0, 255, 0, 255 };
	float multiplier;
	SDL_FRect frame;
};

/*   ����������

����������� ����������� ������� �������������� ������ � ������� ��������.
*/