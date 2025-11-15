#pragma once

#include <vector>
#include "Object.hpp"


class Panel : public Object
{
public:
	// direction - положение панели (горизонтальное - 'h', вертикальное - 'v').
	Panel(
		SDL_Renderer* render, 
		char direction = 'h', 
		float corner_x = 0, 
		float corner_y = 0,
		float object_distance = 20, 
		float distance_of_border_w = 20, 
		float distance_of_border_h = 20
	);

	// Примечание: события обрабатываются также для каждого объекта в панели.
	void process_event(SDL_Event* event) override;

	// Примечание: итерации выполняются также для каждого объекта в панели.
	void iterate() override;

	// Добавить объект в панель.
	void add(std::shared_ptr<Object> object);

	// Удалить объект из панели.
	virtual void remove(int index);

	// Удалить последний объект из панели.
	virtual void pop_back();

	// Удалить все элементы вектора.
	virtual void clear();

	// Количество объектов в панели.
	size_t objects_count();

	// Расстояние между объектами.
	const float& get_object_distance();

	// Расстояние крайних объектов от левой и правой границы.
	const float& get_distance_of_border_w();

	// Расстояние крайних объектов от верхней и нижней границы.
	const float& get_distance_of_border_h();

protected:
	// Найти объект с наибольшей высотой.
	float find_max_height();

	// Найти объект с наибольшей шириной.
	float find_max_width();

	void set_form(const object_form& form, bool default_values = true) override;

	// Выровнять размер панели под объекты.
	void adjust_panel();

	// Установить нужное положение объекта для нахождения в панели.
	void adjust_object(Object* object);

	// Контейнер всех объектов в панели.
	std::vector<std::shared_ptr<Object>> objects;

private:
	float distance_of_border_w;
	float distance_of_border_h;
	float occupied_place = 0;
	float object_distance;
	char direction; // 'h' or 'v'
};

