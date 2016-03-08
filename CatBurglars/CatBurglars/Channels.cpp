#include "Channels.h"

std::vector<Channel> mChannels;


// Sätter den kanalen med givet id till aktiv utifrån givna parametrar
void Channels::setActive(int ID,bool toggle,float holdlength) {
	for (int i = 0; i < mChannels.size(); i++) {

		if (mChannels[i].getID() == ID) {
			
			mChannels[i].setActive(toggle, holdlength);

		}

	}
}

bool Channels::isChannelActive(int ID) {
	for (int i = 0; i < mChannels.size(); i++) {

		if (mChannels[i].getID() == ID) {

			return mChannels[i].isActive();

		}

	}
	
}

void Channels::clearChannels() {
	mChannels.clear();
}

void Channels::update() {
	for (int i = 0; i < mChannels.size(); i++) {
		mChannels[i].runTimer();
	}
}

void Channels::addChannel(Channel c) {
	mChannels.push_back(c);
}
