#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL
#include <string>
#include <vector>
#include "SFML\Window.hpp"
using namespace std;

#include "Tile.h"
#include "Cat.h"
#include "TextureHandler.h"

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;

class Level{
public:
	Level(string filename);
	void update(float dt);
	void render(sf::RenderWindow *window);

	void addPlayer(Cat *cat, int player);
	void load();


private:

	sf::View followPlayer;

	bool mLoaded;
	sf::Sprite mSprite;
	sf::View mView;
	sf::Texture mTexture;
	void generateLevel(string filename);
	string mFile;

	TileRow mTileRow;
	TileRow mTileTopRow;
	TileLayer mBottomTileLayer;
	TileLayer mTopTileLayer;

	int  mMapSizeX, mMapSizeY;


	std::vector<Entity*> mEntities;

};



#endif