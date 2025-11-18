#pragma once

#include <vector>
#include "Object.hpp"


class Panel : public Object
{
public:
	using Object::Object;
	void process(SDL_Event* event) override;
	void iterate() override;

	void add(std::shared_ptr<Object> object);

	virtual void remove(int index);

	virtual void pop_back();

	virtual void clear();

	size_t size();

	const float& get_distance();

	const float& get_distance_of_border_w();

	const float& get_distance_of_border_h();

	// 'v' - vertical, 'h' - horizontal.
	void set_direction(char direction);

	void add_width(float width) = delete;
	void add_height(float height) = delete;

protected:
	float find_max_height();
	float find_max_width();

	void change(
		std::optional<float> x,
		std::optional<float> y,
		std::optional<float> width,
		std::optional<float> height
	) override;

	void adjust_panel();
	void adjust_object(Object* object);
	void adjust_objects();

	std::vector<std::shared_ptr<Object>> objects;

private:
	float distance_of_border_w = 20;
	float distance_of_border_h = 20;
	float occupied_place = 0;
	float object_distance = 10;
	char direction = 'h'; // 'h' or 'v'
};

