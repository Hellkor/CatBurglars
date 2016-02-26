#ifndef INCLUDED_CHANNEL
#define INCLUDED_CHANNEL

#include <SFML\System\Clock.hpp>

class Channel {
public:
	Channel(int channelID);
	bool isActive();
	void setActive(bool toggle , float length);
	int getID();

	void runTimer();
private:
	bool mActive;
	bool mToggled = false;
	int mID;
	void mSetActiveTime(float holdlength);
	float mTimer;
	sf::Clock mClock;
	sf::Time mTime;
};


#endif