#pragma once

#include <vector>
#include "Object.hpp"


class Panel : public Object
{
public:
	//direction - положение панели (гаризонтальное - 'h', вертикальное - 'v').
	//object_distance - дистанция между объектами.
	Panel(SDL_Renderer* render, float corner_x, float corner_y,
		char direction = 'h', float object_distance = 20, 
		float distance_of_border_w = 20, float distance_of_border_h = 20);

	void event_process(SDL_Event* event) override;

	void iterate() override;

	//Добавить объект в панель.
	void add(std::shared_ptr<Object> object);

	//Удалить объект из панели.
	void remove(int index);

	//Удалить последний объект из панели.
	void pop_back();

	//Удалить все элементы вектора.
	void clear();

	std::vector<std::shared_ptr<Object>> objects;

	//Количество объектов в панели.
	size_t objects_count();

	//Найти объект с наибольшей высотой.
	float find_max_height();

	//Найти объект с наибольшей шириной.
	float find_max_width();

protected:
	//Выровнять размер панели под объекты.
	void set_size_for_objects();

private:
	float distance_of_border_w;
	float distance_of_border_h;
	float occupied_place = 0;
	float object_distance;
	char direction; // 'h' or 'v'
};

