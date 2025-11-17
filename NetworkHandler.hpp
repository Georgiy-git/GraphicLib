#pragma once

#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <queue>
#include <atomic>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;
using error_code = boost::system::error_code;

class NetworkHandler
{
public:
	NetworkHandler();

	void async_read();
	void async_connect();

	// Преобразовать int в std::string без изменения информации.
	static std::string from_int(int x);

	void change_endpoint(const std::string& addr, const std::string& port);

	ba::io_context context;
	tcp::socket socket;
	ba::executor_work_guard<ba::io_context::executor_type> work;
	bool connected = false;
	tcp::endpoint endpoint;

private:
	size_t byte_count = 0;
	std::string message;
};

