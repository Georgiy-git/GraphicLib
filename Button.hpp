#pragma once

#include "Object.hpp";

class Button : public Object
{
public:
	Button(SDL_Renderer* render, float center_x, float center_y, float width, float height);

	virtual void event_process(SDL_Event* event) override;

	void remove_pressing();
	void set_pressing();

	bool get_pressing_flag();
	void set_pressing_flag(bool flag);
	
private:
	bool pressing = false;
	bool flag_pressing = false;
};

