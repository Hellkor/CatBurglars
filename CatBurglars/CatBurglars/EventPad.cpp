#include "EventPad.h"
#include "LevelManager.h"

EventPad::EventPad(EVENT_TYPE eventtype, gridvector coords, int dialogID, int dialogRange, DialogManager *dialogmanager, HintManager *hintManager):
	mEventType(eventtype),
	mCoords(coords),
	mDialogID(dialogID),
	mDialogManager(dialogmanager),
	mDialogRange(dialogRange),
	mHintManager(hintManager){

	isActivated = false;
	mPosition.x = mCoords.x * 64;
	mPosition.y = mCoords.y * 64;

}

EventPad::~EventPad()
{
}

bool EventPad::getInteraction(GameObject *g){

	if (Cat *c = dynamic_cast<Cat*>(g)){
		if (g->getCoords() == mCoords  && !isActivated){

			if (mEventType == WIN ){
				isActivated = true;
				//LevelManager::nextLevel();
				return true;
			}
			if (mEventType == DIALOG){
				isActivated = true;
				mDialogManager->startConversation(mDialogID, mDialogRange, 5);
				return false;
			}
			if (mEventType == HINT)
			{
				mHintManager->ShowHint(mDialogID);
				return false;
			}
			if (mEventType == CHECKPOINT)
			{
				return false;
			}
			
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
void EventPad::Render(sf::RenderWindow *window)
{
	if (mEventType == HINT)
	{
		sf::RectangleShape shape1, shape2;
		sf::Color color = sf::Color(255, 0, 0, 191);
		shape1.setFillColor(color);
		shape2.setFillColor(color);
		shape1.setSize(sf::Vector2f(8, 32));
		shape2.setSize(sf::Vector2f(8, 8));
		shape1.setPosition(mPosition.x + 28, mPosition.y + 14);
		shape2.setPosition(mPosition.x + 28, mPosition.y + 50);
		window->draw(shape1);
		window->draw(shape2);
	}
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