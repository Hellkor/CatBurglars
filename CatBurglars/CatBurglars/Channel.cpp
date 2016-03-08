#include "Channel.h"
#include <iostream>



Channel::Channel(int id) :
	mID(id),
	mActive(false),
	mTimer(0),
	mClock(),
	mToggled(false){


}

bool Channel::isActive() {
	return mActive;
}

int Channel::getID() {
	return mID;
}
void Channel::setActive(bool toggle, float holdlength) {

	bool istoggle = toggle;
	float HOLD = holdlength;
	
	if (istoggle && !mActive) {
		mActive = true;
		mToggled = true;
		
	}
	else if (istoggle && mToggled) {
		mToggled = false;
		mActive = false;
	}
	

	if (HOLD > 0 && istoggle == false) {

		mToggled = false;
		mSetActiveTime(HOLD);
		
	}

}

void Channel::mSetActiveTime(float holdlength) {

	mTimer = holdlength;
	mClock.restart();
}


void Channel::runTimer() {
	mTime = mClock.getElapsedTime();

	if (mTime.asSeconds() <= mTimer){
		mActive = true;
	}
	else if (!mToggled){
		mActive = false;
	}
}