#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL
#include <string>
#include <vector>
using namespace std;

#include "Tile.h"
#include "Cat.h"
#include "TextureHandler.h"

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;

class Level{
public:
	Level(string filename, Cat *cat1, Cat *cat2);
	void update(float dt);
	void render(sf::RenderWindow *window);

	void addPlayer(Cat *cat, int player);
	void load();

private:

	void generateLevel(string filename);
	string mFile;

	TileRow mTileRow;
	TileLayer mBottomTileLayer;

	int  mMapSizeX, mMapSizeY;

	Cat *mPlayer1;
	Cat *mPlayer2;

	std::vector<Entity*> mEntities;

};



#endif