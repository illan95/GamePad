#pragma once

#include <boost/asio.hpp>
#include <boost/asio/posix/stream_descriptor.hpp>
#include <boost/bind.hpp>

//#include <iostream>      // for debug output
#include <iomanip>
#include <fstream>
#include <stdlib.h>

#include <linux/input.h> // for input_event
#include <boost/range/adaptor/sliced.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class GamePad {
public:
	explicit GamePad(boost::asio::io_service& io);
	virtual ~GamePad();
	void start();
	void stop();
private:
	boost::asio::io_service& mIo;
	boost::asio::posix::stream_descriptor mSd;
	std::vector<input_event> mEvents;
private:

	void handler_input(boost::system::error_code ec, size_t bytes_transferred);
	void async_read();
	void manage_event(int code,int value,int sec,int usec);
};

