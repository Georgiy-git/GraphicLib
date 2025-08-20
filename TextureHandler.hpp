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

	//num_anim - номер ряда
	//shot_of_anim - количество кадров в анимации
	//delay_ms - задержка перед сменой кадра в милисекундах
	void start_anim(int num_anim = 0, int shot_of_anim = 1, int delay_ms = 50);

	//Изменить отображаемую область изображения.
	void change_show_rect(int column, int row);

	//Итерация.
	void process();

	// Загружает и устанавливает изображение по указанному пути.
	void set_texture(std::string file_name, float frame_w, float frame_h);

	//Установить размер изображения под размер объекта.
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

