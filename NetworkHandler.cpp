#include "NetworkHandler.hpp"
#include <iostream>

NetworkHandler::NetworkHandler()
	: socket(context),
	work(ba::make_work_guard(context))
{

}

void NetworkHandler::async_read()
{
	ba::async_read(socket, ba::buffer(&byte_count, sizeof(byte_count)), [this](error_code ec, size_t bytes) 
		{
			if (ec) {
				connected = false;
				std::cout << ec.message() << std::endl;
				async_connect();
				return;
			}
			message.resize(byte_count, '-');
			ba::async_read(socket, ba::buffer(message.data(), byte_count), [this](error_code ec, size_t bytes)
				{
					if (ec) {
						std::cout << ec.message() << std::endl;
						return;
					}

					std::cout << message << std::endl;
					async_read();
				});
		});
}

void NetworkHandler::async_connect()
{
	if (socket.is_open()) socket.close();

	socket.async_connect(endpoint,
		[&](error_code ec) {
			if (ec) {
				std::cout << ec.message() << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				connected = false;
				async_connect();
			}
			else {
				async_read();
				connected = true;
			}
		});
}
