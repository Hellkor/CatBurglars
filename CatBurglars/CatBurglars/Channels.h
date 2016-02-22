#ifndef INCLUDED_CHANNELS
#define INCLUDED_CHANNELS

#include <vector>
#include <string>
#include "Channel.h"


/*

		Statiska funktioner så att alla klasser kan använda kanalerna

*/

class Channels {


public:
	static void clearChannels();
	static void addChannel(Channel c);

	static bool isChannelActive(int ID);
	static void setActive(int ID, bool toggle, float holdlength);

	static void update();

	void loadChannels(std::string filename);
	

private:

	

};



#endif