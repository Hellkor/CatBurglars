#include <vector>
#include "Level.h"
#include <fstream>
#include <iostream>
using namespace std;

static TextureHandler textures;


// Skapar en level från en textfil
Level::Level(string filename):
	mFile(filename){
	generateLevel(mFile);
	//Initialize again??
	textures.Initialize();
}

// Renderar level
void Level::render(sf::RenderWindow *window){

	window->clear();
	
	
	for (TileLayer::size_type y = 0; y < mBottomTileLayer.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mBottomTileLayer[y].size(); x++)
		{
			mBottomTileLayer[y][x]->Render(window);
		}
	}
		
}

// Laddar in leveln från sparfilen
void Level::generateLevel(string name){

	ifstream inputFile("Maps/" + name + ".txt");
	
	string input;
	inputFile >> input;
	mMapSizeX = stoi(input);
	cout << "Map width: " << mMapSizeX << endl;
	inputFile >> input;
	mMapSizeY = stoi(input);
	cout << "Map height: " << mMapSizeY << endl;
	cout << "Tiles:" << endl;
	for (int y = 0; y < mMapSizeY; y++)
	{
		mTileRow.clear();
		for (int x = 0; x < mMapSizeX; x++)
		{
			inputFile >> input;
			int ID = stoi(input);
			if (ID < 10)
				cout << " " << ID;
			else
				cout << ID;
			cout << " ";
			Tile *tile = new Tile(sf::Vector2i( x * Tile::GetSize().x, y * Tile::GetSize().y), ID, 0, &textures);
			mTileRow.push_back(tile);
		}
		mBottomTileLayer.push_back(mTileRow);

		cout << endl;
	}


}