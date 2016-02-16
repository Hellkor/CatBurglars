#pragma once
#include "Recievers.h"


class MultiDoor : public Recievers{
public:
	MultiDoor(int channel,int numberofchannels, gridvector coords, sf::Texture *texture);

	virtual void connectToChannel(int channelID);

	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();
	virtual bool isSolid();
	virtual bool isInteracting();
private:
	std::vector<int> mChannels;
	int mChannel;
	bool mSolid;
	sf::Vector2i mPosition;
	gridvector mCoords;
	sf::Sprite mSprite;

	bool checkChannels();

	int mActiveChannels;
};