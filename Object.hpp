#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <optional>

#include "TextureHandler.hpp"

using rgb = std::array<uint8_t, 3>;

/*
Примечания:
1)  Любое изменение формы или местоположения объекта должно сопровождаться
	выравниванием текстуры и границ под действительные форму и местоположение объекта.
2)  У каждого объекта должны вызываться функции iterate() и process()
	в соответствующих функциях процесса.
*/


class Object //Базовый класс для всех графических объектов.
{
	friend class TextureHandler;

public:
	Object(SDL_Renderer* renderer, float x, float y, float width, float height);
	Object(SDL_Renderer* renderer, float width, float height);
	Object(SDL_Renderer* renderer);
	virtual void iterate();
	virtual void process(SDL_Event* event);
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

	void set_frame_color(uint8_t r, uint8_t g, uint8_t b);
	void set_frame_multiplier(float x = 1.0);

	// Вход курсора мыши в область объекта.
	bool in() const;

	// Выход курсора мыши из области объекта.
	bool out() const;

	// Возвращает true, если курсор внутри области объекта.
	bool cursor_inside() const;

	void set_x(float x);
	void set_y(float y);
	float get_x();
	float get_y();
	void add_x(float x);
	void add_y(float y);

	void set_width(float width);
	void set_height(float height);
	float get_width();
	float get_height();

	virtual void change(
		std::optional<float> x,
		std::optional<float> y,
		std::optional<float> width,
		std::optional<float> height
	);

protected:
	virtual void adjust();

	void adjust_frame();

	virtual bool inside(float x, float y) const;

	SDL_Renderer* renderer = nullptr;

private:
	float
		x = 0,
		y = 0,
		width = 0,
		height = 0,
		left_border,
		right_border,
		upper_border,
		lower_border;

	bool inside_flag = false;
	bool in_flag = false;
	bool out_flag = false;

	TextureHandler texture_handler;

	// Прорисовка отладочной рамки.
	void iterate_frame();

	bool flag_render_frame = false;
	rgb frame_color = { 0, 255, 0 };
	float multiplier = 1;
	SDL_FRect frame;
};
