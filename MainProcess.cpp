#include "MainProcess.hpp"
#include "Button.hpp"
#include "Panel.hpp"
#include "LineEdit.hpp"

MainProcess::MainProcess(SDL_Renderer* render, NetworkHandler* networkHandler)
	: render{ render }, 
	networkHandler(networkHandler),
	tp(std::chrono::steady_clock::now())
{
	auto* texture = IMG_LoadTexture(render, "textures\\gray_button.svg");

	auto line1 = std::make_shared<Line>("ПАНЕЛЬ УПРАВЛЕНИЯ", render, 0.5, 50, 50, 5);
	objects.push_back(line1);

	auto panel1 = std::make_shared<Panel>(render, 'v', 50, 200, 20, 0);
	objects.push_back(panel1);

	auto panel2 = std::make_shared<Panel>(render, 'h', 0, 0, 10, 0, 0);
	panel1->add(panel2);

	auto line2 = std::make_shared<Line>("Сервер:", render);
	panel2->add(line2);

	auto lineEdit1 = std::make_shared<LineEdit>(render, 16, 0.3, 0, 0, 1, 20);
	_lineEdit1 = lineEdit1.get();
	lineEdit1->set_text("192.1.1.5");
	panel2->add(lineEdit1);

	auto panel3 = std::make_shared<Panel>(render, 'h', 0, 0, 20, 0, 0);
	panel1->add(panel3);

	auto line6 = std::make_shared<Line>("Порт:", render);
	panel3->add(line6);

	auto lineEdit3 = std::make_shared<LineEdit>(render, 5);
	_lineEdit3 = lineEdit3.get();
	lineEdit3->set_text("14000");
	panel3->add(lineEdit3);

	auto line3 = std::make_shared<Line>("Состояние: не отвечает", render);
	_line3 = line3.get();
	panel1->add(line3);

	auto line4 = std::make_shared<Line>("Подключенные системы: 0", render);
	panel1->add(line4);

	auto object1 = std::make_shared<Object>(render, 0, 0, 0, 50);
	panel1->add(object1);

	auto line5 = std::make_shared<Line>("Послать команду вручную:", render);
	panel1->add(line5);

	auto lineEdit2 = std::make_shared<LineEdit>(render, 25, 0.3, 0, 0, 3, 10);
	_lineEdit2 = lineEdit2.get();
	panel1->add(lineEdit2);

	networkHandler->change_endpoint(_lineEdit1->get_text(), _lineEdit3->get_text());
	networkHandler->async_connect();
}

void MainProcess::iterate() 
{
	for (auto object : objects) {
		object->iterate();
	}

	if (!networkHandler->connected && connected) {
		connected = false;
		_line3->set_text("Соединение: не отвечает");
	}
	else if (networkHandler->connected && !connected) {
		connected = true;
		_line3->set_text("Соединение: установлено");
	}
}

void MainProcess::event(SDL_Event* event) 
{
	if (event->type == SDL_EVENT_MOUSE_MOTION) {
		
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		
	}
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {

	}
	else if (event->type == SDL_EVENT_KEY_DOWN) {
		if (event->key.scancode == SDL_SCANCODE_RETURN && 
			(_lineEdit1->has_focus() || _lineEdit3->has_focus())) 
		{
			if (networkHandler->socket.is_open()) networkHandler->socket.close();
			auto text = _lineEdit1->get_text();
			networkHandler->change_endpoint(_lineEdit1->get_text(), _lineEdit3->get_text());
		}
		else if (event->key.scancode == SDL_SCANCODE_RETURN && _lineEdit2->has_focus()) {
			if (networkHandler->connected) {
				std::string command = _lineEdit2->get_text();
				command = NetworkHandler::from_int(command.size()) + command;
				ba::async_write(networkHandler->socket, ba::buffer(command.data(), command.size()),
					[=](error_code ec, size_t bytes){
						if (ec) {
							std::cout << ec.message() << std::endl;
						}
						_lineEdit2->clear();
					});
			}
		}
	}

	for (auto object : objects) {
		object->process_event(event);
	}
}
