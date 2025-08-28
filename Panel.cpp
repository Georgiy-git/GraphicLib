#include "Panel.hpp"


Panel::Panel(SDL_Renderer* render, float center_x, float center_y,
	char direction, float object_distance, float distance_of_border_w, float distance_of_border_h)
	: Object(render, center_x, center_y, 0, 0),
	object_distance{ object_distance }, direction{ direction }, 
	distance_of_border_h{ distance_of_border_h }, distance_of_border_w{ distance_of_border_w }
{
	
}

void Panel::event_process(SDL_Event* event)
{
	Object::event_process(event);

	for (auto object : objects) {
		object->event_process(event);
	}
}

void Panel::iterate() {
	Object::iterate();
	for (auto object : objects) {
		object->iterate();
	}
}

void Panel::add(std::shared_ptr<Object> object)
{
	if (direction == 'h') {
		object->set_form(
			{ 
				.corner_x = this->get_form().corner_x + occupied_place + distance_of_border_w,
				.corner_y = this->get_form().corner_y + distance_of_border_h 
			}
		);
		occupied_place += object->get_form().width + object_distance;
	}

	else if (direction == 'v') {
		object->set_form(
			{ 
				.corner_x = this->get_form().corner_x + distance_of_border_w,
				.corner_y = this->get_form().corner_y + occupied_place + distance_of_border_h
			}
		);
		occupied_place += object->get_form().height + object_distance;
	}

	objects.push_back(object);
	set_size_for_objects();
}

void Panel::remove(int index)
{
	auto object = std::find_if(objects.begin(), objects.end(), 
		[&](std::shared_ptr<Object> obj) { return obj == objects[index]; });

	if (direction == 'h') {
		float corner_x = (*object)->get_form().corner_x;
		for (size_t i = index + 1; i < objects_count(); ++i) {
			objects[i]->set_form({ .corner_x = corner_x });
			corner_x += objects[i]->get_form().width + object_distance;
		}
		occupied_place -= (*object)->get_form().width + object_distance;
	}
	else if (direction == 'v') {
		float corner_y = (*object)->get_form().corner_y;
		for (size_t i = index + 1; i < objects_count(); ++i) {
			objects[i]->set_form({ .corner_y = corner_y });
			corner_y += objects[i]->get_form().height + object_distance;
		}
		occupied_place -= (*object)->get_form().height + object_distance;
	}

	objects.erase(object);
	set_size_for_objects();
}

void Panel::pop_back() {
	if (objects_count() == 0) return;

	if (direction == 'h') {
		occupied_place -= objects.back()->get_form().width + object_distance;
	}
	else if (direction == 'v') {
		occupied_place -= objects.back()->get_form().height + object_distance;
	}
	objects.pop_back();
	set_size_for_objects();
}

void Panel::clear() {
	objects.clear();
	occupied_place = 0;
}

void Panel::set_size_for_objects()
{
	float w, h;
	if (direction == 'h') {
		w = distance_of_border_w * 2;
		for (auto object : objects) {
			w += object->get_form().width;
		}
		if (objects_count() > 1) w += (objects_count() - 1) * object_distance;
		h = distance_of_border_h * 2 + find_max_height();
		set_form({ .width = w, .height = h });
	}
	else if (direction == 'v') {
		float h = distance_of_border_h * 2;
		for (auto object : objects) {
			h += object->get_form().height;
		}
		if (objects_count() > 1) h += (objects_count() - 1) * object_distance;
		w = distance_of_border_w * 2 + find_max_width();
		set_form({ .width = w, .height = h });
	}
}

size_t Panel::objects_count() {
	return objects.size();
}

float Panel::find_max_height()
{
	float max = -1;
	for (auto object : objects) {
		if (object->get_form().height > max) max = object->get_form().height;
	}
	return max;
}

float Panel::find_max_width()
{
	float max = -1;
	for (auto object : objects) {
		if (object->get_form().width > max) max = object->get_form().width;
	}
	return max;
}
