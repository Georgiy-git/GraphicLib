#pragma once

#include "Object.hpp"

class Person : public Object
{
public:
	Person(SDL_Renderer* render, float corner_x, float corner_y);
	void iterate() override;
	void event_process(SDL_Event* event) override;

	void step();

	void turn_around();

private:
	bool inside(float x, float y) const override;
};

