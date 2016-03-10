#pragma once

#include <string>
#include <vector>
using namespace std;

#include "Tile.h"
#include "Cat.h"
#include "TextureHandler.h"
#include "Controller.h"

typedef vector<Tile*> TileRow;
typedef vector<TileRow> TileLayer;

class Level{
public:
	Level(string filename);
	void update(float dt);
	void render(sf::RenderWindow *window);

	void addPlayer(Cat *cat, int player);
	void load();


	void InitializeGuiView(sf::RenderWindow *window);
private:
	bool mLoaded;
	void renderLight(sf::RenderWindow *window);

	void renderPlayerFOV(sf::RenderWindow *window, int player);

	void generateLevel(string filename);
	string mFile;
	string mLevelType;

	TileRow mTileRow;
	TileRow mTileTopRow;

	TileLayer mBottomTileLayer;
	TileLayer mWallTileLayer;
	TileLayer mTopTileLayer;

	int  mMapSizeX, mMapSizeY;


	std::vector<Entity*> mEntities;

	sf::View mPlayer1View;
	sf::View mPlayer2View;
	sf::View guiView;
	
	Controller p1Controller;
	Controller p2Controller;
	Controller p1Joystick;
	Controller p2Joystick;

	int mPlayers;

	void generateView();
	void updateViews();

};



