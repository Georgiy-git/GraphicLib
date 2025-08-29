#pragma once

#include <vector>
#include "Object.hpp"


class Panel : public Object
{
public:
	//direction - ��������� ������ (�������������� - 'h', ������������ - 'v').
	//object_distance - ��������� ����� ���������.
	Panel(SDL_Renderer* render, float corner_x, float corner_y,
		char direction = 'h', float object_distance = 20, 
		float distance_of_border_w = 20, float distance_of_border_h = 20);

	void event_process(SDL_Event* event) override;

	void iterate() override;

	//�������� ������ � ������.
	void add(std::shared_ptr<Object> object);

	//������� ������ �� ������.
	void remove(int index);

	//������� ��������� ������ �� ������.
	void pop_back();

	//������� ��� �������� �������.
	void clear();

	std::vector<std::shared_ptr<Object>> objects;

	//���������� �������� � ������.
	size_t objects_count();

	//����� ������ � ���������� �������.
	float find_max_height();

	//����� ������ � ���������� �������.
	float find_max_width();

protected:
	//��������� ������ ������ ��� �������.
	void set_size_for_objects();

private:
	float distance_of_border_w;
	float distance_of_border_h;
	float occupied_place = 0;
	float object_distance;
	char direction; // 'h' or 'v'
};

