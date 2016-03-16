#ifndef INCLUDED_CHANNEL
#define INCLUDED_CHANNEL

#include <SFML\System\Clock.hpp>

class Channel {
public:
	Channel(int channelID);
	bool isActive();
	int getID();



	void activate();
	void deactivate();
private:
	bool mActive;
	bool mToggled = false;
	int mID;
	float mTimer;
	sf::Clock mClock;
	sf::Time mTime;
};


#endif