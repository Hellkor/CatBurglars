#include <vector>
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Channel.h"
#include "Channels.h"
#include "Button.h"
#include "Door.h"
#include "Crate.h"
using namespace std;
#include "Controller.h"
Controller c;
static TextureHandler textures;


// Skapar en level från en textfil
Level::Level(string filename) :
	mFile(filename){

	//Initialize textures
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
	for each (Entity *e in mEntities){
		e->Render(window);
	}
		
}

void Level::addPlayer(Cat *cat , int player){
	


}
void Level::update(float dt){

	Channels::update();

	if (Channels::isChannelActive(1)){
		cout << "Channel 1 is activated!" << endl;
	}

	for each (Entity *e in mEntities){

		e->Update(dt);
		
		
		if (Cat *cat = dynamic_cast<Cat*>(e)){

			c.move(cat, &mBottomTileLayer, &mEntities);
			
			for each (Entity *b in mEntities){
				
				if (Usable *u = dynamic_cast<Usable*>(b)){
					u->getInteraction(cat);
				}

				if (Crate *object = dynamic_cast<Crate*>(b)){
					//object->getInteraction(cat);
				}
			}
			

		}
		

	}

}

void Level::load(){
	mEntities.clear();
	generateLevel(mFile);
	//mEntities.push_back(new Cat(textures.GetTexture(10),gridvector(0,0),1));
	

	Channel c = Channel(1);
	Channels::addChannel(c);

	Button *butt = new Button(1, textures.GetTexture(12), gridvector(3,3));
	Button *b = new Button(1, textures.GetTexture(12), gridvector(7, 9));
	Door *d = new Door(1, gridvector(9, 4), textures.GetTexture(10));

	mEntities.push_back(d);
	mEntities.push_back(b);
	mEntities.push_back(butt);

	mEntities.push_back(new Crate(textures.GetTexture(4), gridvector(2, 2), 1));
	mEntities.push_back(new Crate(textures.GetTexture(4), gridvector(4, 4), 1));
	mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(1, 1), 2));
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
			Tile *tile = new Tile(gridvector( x , y ), ID, 0, &textures);
			mTileRow.push_back(tile);
		}
		mBottomTileLayer.push_back(mTileRow);

		cout << endl;
	}


}