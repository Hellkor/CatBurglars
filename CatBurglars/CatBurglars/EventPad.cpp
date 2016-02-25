#include "EventPad.h"
#include "LevelManager.h"

EventPad::EventPad(EVENT_TYPE eventtype, gridvector coords, int dialogID, DialogManager *dialogmanager):
	mEventType(eventtype),
	mCoords(coords),
	mDialogID(dialogID),
	mDialogManager(dialogmanager){

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
				mDialogManager->showDialog(mDialogID,5);
			}
			isActivated = true;
			return true;
		}
		else return false;
	}
	else return false;
}
bool Activate(sf::Time active_time) {
	return true;
}
bool playSound() {
	return true;
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
Layer EventPad::getLayer() {
	return FRONT;
}