#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL
#include <string>
#include <vector>
#include "Tile.h"
#include "Cat.h"
#include "TextureHandler.h"
#include "Controller.h"

#include "SFML\Window.hpp"
using namespace std;


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

	bool mLoaded;
	void renderLight(sf::RenderWindow *window);

	void renderPlayerFOV(sf::RenderWindow *window, int player);




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

	sf::View mPlayer1View;
	sf::View mPlayer2View;
	sf::View guiView;
	
	Controller p1Controller;
	Controller p2Controller;

	int mPlayers;

	void generateView();
	void updateViews();

};



#endif