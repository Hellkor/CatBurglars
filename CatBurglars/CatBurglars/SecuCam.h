#pragma once

#include "Recievers.h"
#include "Channels.h"

class secuCam :public Recievers{

public:

	secuCam(int channel, gridvector coords, sf::Texture *texture);
	//~secuCam();
	virtual void connectToChannel(int channelID);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	//virtual bool isSolid(); //kanske ska va solid, kanske inte, h�r med design imorgon
	virtual bool isInteracting();
	 bool isOn;

private:
	int mChannel;
	bool mOn;
	//bool mSolid; //samma som med isSolid();
	sf::Vector2i mPosition;
	gridvector mCoords;
	sf::Sprite mSprite;

};
