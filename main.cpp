
#include "gamepad.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using namespace boost::asio;

int main(int argc, const char* argv[])
{
	boost::asio::io_service io;

	boost::shared_ptr<GamePad> objGamePad = boost::make_shared <GamePad> (io);
	objGamePad->start();
	io.run();
	return 0;
}
