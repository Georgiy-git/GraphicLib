#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <memory>
#include <iostream>

#include "TextureHandler.hpp"

using rgb = std::array<uint8_t, 3>;

struct object_form {
	float
	corner_x,
	corner_y,
	width,
	height,
	left_border,
	right_border,
	upper_border,
	lower_border;
};

class Object //Базовый класс для всех графических объектов.
{
	friend class TextureHandler;

public:
	// Соответственно init, iter, event и quit.
	Object(SDL_Renderer* render, float corner_x, float corner_y, float width, float height);
	virtual void iterate();
	virtual void process_event(SDL_Event* event);
	virtual ~Object();

	// Возвращает размер экрана.
	static std::pair<int, int> get_display_size();

	// Устанавливает загруженное изображение.
	void set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_py);

	// Изменение отображаемого кадра.
	void change_show_rect(int column, int row);

	// num - номер ряда
	// shot - количество кадров в анимации
	// delay_ms - задержка перед сменой кадра в миллисекундах
	void start_animation(int num = 0, int shot = 1, int delay_ms = 50);

	// Установить отладочную рамку.
	void render_frame(bool flag);

	// Установка цвета отладочной рамки.
	void set_frame_color(uint8_t r, uint8_t g, uint8_t b);

	// Задаёт размер рамки кратности x.
	void set_frame_size(float x = 1);

	// Смещение на x по горизонтали.
	void add_x(float x);

	// Смещение на y по вертикали.
	void add_y(float y);

	// Установить местоположение на экране.
	void set_x(float x);
	void set_y(float y);

	void set_width(float width);
	void set_height(float height);

	const object_form& get_form() const;

	// Вход курсора мыши в область объекта.
	bool in() const;

	// Выход курсора мыши из области объекта.
	bool out() const;

	// Возвращает true, если курсор внутри области объекта.
	bool cursor_inside() const;

protected:
	// При default_values = true нулевые значения переданной структуры учитываться не будут.
	virtual void set_form(const object_form& form, bool default_values = true);

	object_form form;

	virtual bool inside(float x, float y) const;

	SDL_Renderer* render = nullptr;

private:
	bool inside_flag = false;
	bool in_flag = false;
	bool out_flag = false;

	TextureHandler texture_handler;

	// Прорисовка отладочной рамки.
	void iterate_frame();

	bool flag_render_frame = false;
	rgb frame_color = { 0, 255, 0 };
	float multiplier;
	SDL_FRect frame;
};
