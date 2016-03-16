#include "Channels.h"

std::vector<Channel> mChannels;




bool Channels::isChannelActive(int ID) {
	for (int i = 0; i < mChannels.size(); i++) {

		if (mChannels[i].getID() == ID) {

			return mChannels[i].isActive();

		}

	}
	
}

void Channels::activate(int channel) {
	for (int i = 0; i < mChannels.size(); i++) {

		if (mChannels[i].getID() == channel) {

			mChannels[i].activate();

		}

	}

}
void Channels::deactivate(int channel) {
	for (int i = 0; i < mChannels.size(); i++) {

		if (mChannels[i].getID() == channel) {

			mChannels[i].deactivate();

		}

	}

}

void Channels::clearChannels() {
	mChannels.clear();
}

void Channels::update() {
	
}

void Channels::addChannel(Channel c) {
	mChannels.push_back(c);
}
