#include "EventPad.h"
#include "LevelManager.h"

EventPad::EventPad(EVENT_TYPE eventtype, gridvector coords):
	mEventType(eventtype),
	mCoords(coords){

	isActivated = false;
	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

}

bool EventPad::getInteraction(GameObject *g){

	if (Cat *c = dynamic_cast<Cat*>(g)){
		if (g->getCoords() == mCoords  && !isActivated){

			if (mEventType == WIN){
				LevelManager::nextLevel();
			}
			if (mEventType == DIALOG){
				cout << "Dialog!" << endl;
			}
			isActivated = true;
			return true;
		}
		else return false;
	}
	else return false;
		

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