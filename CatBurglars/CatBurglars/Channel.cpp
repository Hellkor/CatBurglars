#include "Channel.h"
#include <iostream>



Channel::Channel(int id) :
	mID(id),
	mActive(false),
	mTimer(0),
	mClock(),
	mToggled(false){


}
void Channel::activate() {
	mActive = true;
}
void Channel::deactivate() {
	mActive = false;
}
bool Channel::isActive() {
	return mActive;
}

int Channel::getID() {
	return mID;
}

