#include "MainProcess.hpp"
#include "Button.hpp"
#include "Panel.hpp"
#include "Line.hpp"
#include "LineEdit.hpp"

MainProcess::MainProcess(SDL_Renderer* render)
	: render{ render }
{
	auto* texture = IMG_LoadTexture(render, "textures\\gray_button.svg");
	Line::set_default_font(render);

	auto line1 = std::make_shared<Line>("ПАНЕЛЬ УПРАВЛЕНИЯ", render, 0.5, 50, 50, 5);
	objects.push_back(line1);

	auto panel1 = std::make_shared<Panel>(render, 'v', 50, 200, 20, 0);
	objects.push_back(panel1);

	auto panel2 = std::make_shared<Panel>(render, 'h', 0, 0, 10, 0, 0);
	panel1->add(panel2);

	auto line2 = std::make_shared<Line>("Сервер: ", render);
	panel2->add(line2);

	auto lineEdit1 = std::make_shared<LineEdit>(render, 16, 0.3, 0, 0, 1, 20);
	lineEdit1->set_text("127.0.0.1");
	panel2->add(lineEdit1);

	auto line3 = std::make_shared<Line>("Состояние: не отвечает", render);
	panel1->add(line3);

	auto line4 = std::make_shared<Line>("Подключенные системы: 0", render);
	panel1->add(line4);
}

void MainProcess::iterate() {
	for (auto object : objects) {
		object->iterate();
	}
}

void MainProcess::event(SDL_Event* event) {
	for (auto object : objects) {
		object->process_event(event);
	}

	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {

	}
}