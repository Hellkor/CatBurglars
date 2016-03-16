#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include "TextureHandler.h"
#include "gridvector.h"

class Tile : public Entity
{
public:
	Tile(gridvector coords, int ID, int textureID, TextureHandler *textures, string leveltype);
	~Tile();
	void Render(sf::RenderWindow *mainWindow);
	void Update(float dt);
	//Added
	sf::Vector2i GetPosition();
	static sf::Vector2i GetSize();
	static void IDChangeInfo(int ID, bool allowed);
	int GetID();
	gridvector getCoords();
	virtual Layer getLayer();
	
	void setAlpha(int alpha);
private:
	int mID = 0;
	gridvector mCoords;
	//Added
	sf::Sprite mSprite;
	sf::Vector2i mPosition;
};

#endif