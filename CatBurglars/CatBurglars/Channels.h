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

	static void update();

	

	static void activate(int channel);
	static void deactivate(int channel);

private:

	

};



#endif