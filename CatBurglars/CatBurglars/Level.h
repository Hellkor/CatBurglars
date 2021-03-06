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
enum StageType { Cutscene, GameStage };

class Level{
	
public:
	Level(string filename);
	Level(int movieID);
	void update(float dt);
	void render(sf::RenderWindow *window);

	void addPlayer(Cat *cat, int player);
	void load();
	void Clear();

	void InitializeGuiView(sf::RenderWindow *window);

	static void setResolution(int x,int y);
private:
	StageType mType;

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
	
	int mMovieID;

	int mPlayers;

	void generateView();
	void updateViews();

	bool lost = false;
	sf::Time deathDelay;
	sf::Clock deathClock;

	bool win = false;
	int length(int x, int y);

	sf::Clock douglasUpdateClock;
	sf::Time douglasUpdateDelay = sf::seconds(1);


	sf::Sound FailSound;
};



