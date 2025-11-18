#include "Panel.hpp"


void Panel::process(SDL_Event* event)
{
	Object::process(event);

	for (auto object : objects) {
		object->process(event);
	}
}

void Panel::iterate() 
{
	Object::iterate();

	for (auto object : objects) {
		object->iterate();
	}
}

void Panel::add(std::shared_ptr<Object> object)
{
	objects.push_back(object);
	adjust_object(object.get());
	adjust_panel();
}

void Panel::remove(int index)
{
	auto object = std::find_if(objects.begin(), objects.end(), 
		[&](std::shared_ptr<Object> obj) { return obj == objects[index]; });

	if (object == objects.end()) 
		throw std::exception("Remove: there is no object by index.");

	if (direction == 'h') {
		float corner_x = (*object)->get_x();
		for (size_t i = index + 1; i < size(); ++i) {
			objects[i]->set_x(corner_x);
			corner_x += objects[i]->get_width() + object_distance;
		}
		occupied_place -= (*object)->get_width() + object_distance;
	}
	else if (direction == 'v') {
		float corner_y = (*object)->get_y();
		for (size_t i = index + 1; i < size(); ++i) {
			objects[i]->set_y(corner_y);
			corner_y += objects[i]->get_height() + object_distance;
		}
		occupied_place -= (*object)->get_height() + object_distance;
	}

	objects.erase(object);
	adjust_panel();
}

void Panel::pop_back() 
{
	if (size() == 0) return;

	if (direction == 'h') {
		occupied_place -= objects.back()->get_width() + object_distance;
	}
	else if (direction == 'v') {
		occupied_place -= objects.back()->get_height() + object_distance;
	}
	objects.pop_back();
	adjust_panel();
}

void Panel::clear() 
{
	objects.clear();
	occupied_place = 0;
}

void Panel::adjust_panel()
{
	float w, h;
	if (direction == 'h') {
		w = distance_of_border_w * 2;
		for (auto object : objects) {
			w += object->get_width();
		}
		if (size() > 1) w += (size() - 1) * object_distance;
		h = distance_of_border_h * 2 + find_max_height();
		set_width(w);
		set_height(h);
	}
	else if (direction == 'v') {
		float h = distance_of_border_h * 2;
		for (auto object : objects) {
			h += object->get_height();
		}
		if (size() > 1) h += (size() - 1) * object_distance;
		w = distance_of_border_w * 2 + find_max_width();
		set_width(w);
		set_height(h);
	}
}

size_t Panel::size() 
{
	return objects.size();
}

float Panel::find_max_height()
{
	float max = -1;
	for (auto object : objects) {
		if (object->get_height() > max) max = object->get_height();
	}
	return max;
}

float Panel::find_max_width()
{
	float max = -1;
	for (auto object : objects) {
		if (object->get_width() > max) max = object->get_width();
	}
	return max;
}

void Panel::change(
	std::optional<float> x, 
	std::optional<float> y, 
	std::optional<float> width, 
	std::optional<float> height)
{
	Object::change(x, y, width, height);
	for (auto& object : objects) {
		object->change(x, y, width, height);
	}
}

const float& Panel::get_distance()
{
	return object_distance;
}

const float& Panel::get_distance_of_border_w()
{
	return distance_of_border_w;
}

const float& Panel::get_distance_of_border_h()
{
	return distance_of_border_h;
}

void Panel::set_direction(char direction)
{
	this->direction = direction;
	adjust_objects();
	adjust_panel();
}

void Panel::adjust_object(Object* object)
{
	if (direction == 'h') {
		object->set_x(get_x() + occupied_place + distance_of_border_w);
		object->set_y(get_y() + distance_of_border_h);
		occupied_place += object->get_width() + object_distance;
	}

	else if (direction == 'v') {
		object->set_x(get_x() + distance_of_border_w);
		object->set_y(get_y() + occupied_place + distance_of_border_h);
		occupied_place += object->get_height() + object_distance;
	}
}

void Panel::adjust_objects()
{
	occupied_place = 0;
	for (auto object : objects) {
		adjust_object(object.get());
	}
}

