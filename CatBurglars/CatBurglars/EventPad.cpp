#include "EventPad.h"


EventPad::EventPad(EVENT_TYPE eventtype, gridvector coords):
	mEventType(eventtype),
	mCoords(coords){

	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

}

bool EventPad::getInteraction(GameObject *g){

	if (!isActivated){

		if (g->getCoords() == mCoords && g->isInteracting()){
			
			if (mEventType == WIN){
				cout << "Win!" << endl;
			}
			if (mEventType == DIALOG){
				cout << "Dialog!" << endl;
			}
			
			return true;
		}

	}

}
void EventPad::Update(float dt){

}
void EventPad::Render(sf::RenderWindow *window){

}
int EventPad::getChannelID(){
	return mChannelID;
}
bool EventPad::isInteracting(){
	return false;
}
bool EventPad::isSolid(){
	return false;
}
gridvector EventPad::getCoords(){
	return mCoords;
}
sf::Vector2i EventPad::GetPosition(){
	return mPosition;
}