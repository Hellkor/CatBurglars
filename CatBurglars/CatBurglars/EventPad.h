#ifndef INCLUDED_EVENTPAD
#define INCLUDED_EVENTPAD

#include "Usable.h"
#include "gridvector.h"
#include "DialogManager.h"
enum EVENT_TYPE { WIN, DIALOG };
class EventPad : public Usable{
	
public:

	EventPad(EVENT_TYPE eventtype, gridvector coords, int dialogID,int dialogRange,DialogManager *dialogmanager);
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();
	virtual bool getInteraction(GameObject *g);
	virtual int getChannelID();
	virtual bool isSolid();
	virtual Layer getLayer();
	virtual bool isInteracting();

	bool Activate(sf::Time active_time);
	bool playSound();
private:
	int mDialogID;
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
	gridvector mCoords;
	int mChannelID;
	bool isActivated;
	EVENT_TYPE mEventType;
	DialogManager *mDialogManager;
	int mDialogRange;
	
};



#endif