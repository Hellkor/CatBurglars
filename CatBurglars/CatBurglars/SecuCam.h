#pragma once

#include "Recievers.h"
#include "Channels.h"
#include <SFML/Graphics.hpp>


class secuCam : public Recievers{

public:

	secuCam(int channel, gridvector coords, sf::Texture *texture,int range,int direction);
	~secuCam();
	virtual void connectToChannel(int channelID);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	virtual sf::Vector2i getDirection();
	virtual gridvector getCoords();
	virtual bool isInteracting();



	


	bool getIntersection(GameObject *obj);

	virtual bool isSolid();


private:
	sf::ConvexShape mConvex;
	std::vector<gridvector*> mVision;
	int mChannel;
	
	bool isOn;
	//bool mSolid; //samma som med isSolid();
	sf::Vector2i mPosition;
	sf::Vector2i mDirection;
	gridvector mCoords;
	sf::Sprite mSprite;
	sf::Sprite mHitboxSprite;



};
