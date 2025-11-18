#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <chrono>


class TextureHandler
{
public:
	TextureHandler(SDL_Renderer* renderer, float& x, float& y, float& width, float& height);

	// num - номер ряда
	// shot - количество кадров в анимации
	// delay_ms - задержка перед сменой кадра в миллисекундах
	void start_animation(int num = 0, int shot = 1, int delay_ms = 50);

	// Изменить отображаемую область изображения.
	void change_show_rect(int column, int row);

	// Итерация.
	void iterate();

	// Устанавливает загруженное изображение.
	void set_texture(SDL_Texture* texture, int frame_w_px, int frame_h_px);

	// Установить размер и положение изображения под размер и положение объекта.
	void adjust();

protected:
	float& x;
	float& y;
	float& width;
	float& height;
	SDL_Renderer* renderer;

	std::chrono::steady_clock::time_point animation_start;
	std::chrono::microseconds delay;
	int shot_of_anim = 0;
	int shot_num = 0;
	bool is_playing = false;

	SDL_Texture* texture = nullptr;
	SDL_FRect show_rect;
	SDL_FRect size_rect;
};

