#pragma once

#include "Channels.h" 
#include "Recievers.h"
#include <SFML/Graphics.hpp>
#include "TextureHandler.h"

class Lazer : public Recievers {

public:
	Lazer(int channel, int channelRange, gridvector coords, sf::Texture *texture, int range, string direction);
	virtual ~Lazer();
	virtual void connectToChannel(int channelID);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	virtual sf::Vector2i getDirection();
	virtual gridvector getCoords();
	virtual bool isInteracting();

	bool getIntersection(GameObject *obj);
	virtual Layer getLayer();
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

	string mFace;

	std::vector<int> mChannels;
	bool checkChannels();
	int mActiveChannels;


};