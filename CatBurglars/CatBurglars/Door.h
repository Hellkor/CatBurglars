#pragma once
#include "Recievers.h"
#include "Channels.h"
class Door : public Recievers{
public:
	Door(int channel, gridvector coords, sf::Texture *texture);
	virtual void connectToChannel(int channelID);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow *window);
	virtual sf::Vector2i GetPosition();
	virtual bool isSolid();
private:
	int mChannel;
	bool mSolid;
	sf::Vector2i mPosition;
	gridvector mCoords;
	sf::Sprite mSprite;
};