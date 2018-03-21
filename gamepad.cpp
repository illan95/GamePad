
#include "gamepad.h"



GamePad::GamePad(boost::asio::io_service& io): 
	mIo(io), mSd(io), mEvents()
{

}

GamePad::~GamePad() {

}

void GamePad::start()
{
	boost::system::error_code error;
	int dev;
	for(int i=0;i<5;i++) {
		dev = open("/dev/input/event6", O_RDONLY);
		if(dev == -1){
			std::cout << "[GamePad::start] Error when opening the GamePad" << std::endl;
			boost::this_thread::sleep(boost::posix_time::seconds(10));
		} else {
			break;
		}
	}
	mSd.assign(dev,error);
	if(!error) {
		std::cout << "[GamePad::start] Assigned!" << std::endl; 
		mSd.non_blocking(true);
	}
	async_read();
}

void GamePad::stop()
{
	//std::cout << "Turning off the computer" << std::endl;
	system("/home/gco/Descargas/OpenC2X/scripts/stopOpenC2X.sh");
	system("rm /etc/rc5.d/S06init.sh");
	system("pkill gpsd");
	system("pkill rfcomm");
	system("poweroff");
}


void GamePad::handler_input(boost::system::error_code ec, size_t bytes_transferred)
{
        if (!ec) {
        	auto const n = bytes_transferred / sizeof(input_event);
		for(size_t i=0; i<n; ++i) {
			auto& ev = mEvents[i];
                	//using namespace boost::posix_time;
	                //ptime ts({1970,1,1}, seconds(ev.time.tv_sec) + microsec(ev.time.tv_usec));
	                //std::cout << std::dec << ts.time_of_day() << "\t" << std::hex << std::hex << ev.type << " " << ev.code  << " " << ev.value << "\n";
			manage_event(ev.code,ev.value,ev.time.tv_sec,ev.time.tv_usec);
		}
	        //std::cout << "\n";
	        async_read();
        } else {
            std::cerr << ec.message() << "\n";
        }

}


void GamePad::async_read()
{
	mEvents.resize(32);
	mSd.async_read_some(boost::asio::buffer(mEvents), boost::bind(&GamePad::handler_input, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void GamePad::manage_event(int code,int value,int sec,int usec)
{
	//std::cout << "[GamePad::manage_value] The value is: " << value << std::endl;
	if((code == 304 || code == 168) && value == 1){
		boost::posix_time::ptime ts({1970,1,1}, boost::posix_time::seconds(sec) + boost::posix_time::microsec(usec));
		//std::cout << ts.time_of_day() << std::endl;
		std::ofstream myfile1;
                myfile1.open ("/home/gco/Descargas/Logs/GamePad.txt",std::ios::app); // opens the file and writes at the end
                myfile1 << ts.time_of_day() << "\n";
                myfile1.close();
	}
	else if(code == 1 && value == 2){
		stop();
	}
}
