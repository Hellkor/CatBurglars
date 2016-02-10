#include <vector>
#include "Level.h"
#include <fstream>
#include <iostream>
#include "Channel.h"
#include "Channels.h"
#include "Button.h"
#include "Door.h"
#include "Crate.h"
#include "Guard.h"
using namespace std;
#include "Controller.h"
Controller controller;
static TextureHandler textures;
static SoundHandler soundhandler;

// Skapar en level från en textfil
Level::Level(string filename) :
	mFile(filename){

	//Initialize textures
	textures.Initialize();
	soundhandler.Initialize();
}

// Renderar level
void Level::render(sf::RenderWindow *window){

	window->clear();


	
	for (TileLayer::size_type y = 0; y < mBottomTileLayer.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mBottomTileLayer[y].size(); x++)
		{
			mBottomTileLayer[y][x]->Render(window);
			mTopTileLayer[y][x]->Render(window);
		}
	}
	/*for (TileLayer::size_type y = 0; y < mTopTileLayer.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mTopTileLayer[y].size(); x++)
		{
			mTopTileLayer[y][x]->Render(window);
		}
	}*/
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
		
		if (GameObject *obj = dynamic_cast<GameObject*>(e)){

			if (Guard *guard = dynamic_cast<Guard*>(obj)){

				guard->AImovement(&mTopTileLayer, &mEntities);
			}
				for each (Entity *ent in mEntities){

					if (Usable *u = dynamic_cast<Usable*>(ent)){
						u->getInteraction(obj);
					}
				}
			

		}
		if (Cat *cat = dynamic_cast<Cat*>(e)){

			controller.move(cat, &mTopTileLayer, &mEntities);
				
		}
		

	}

}

void Level::load(){

	mEntities.clear();
	generateLevel(mFile);

	Channel c = Channel(1);
	Channels::addChannel(c);
	Channels::addChannel(Channel(2));
	Channels::addChannel(Channel(3));
	Channels::addChannel(Channel(5));

	mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(1, 1), 2, &soundhandler));
	//mEntities.push_back(new Guard(textures.GetTexture(10), gridvector(10, 10), 1,"testAI"));
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
	//Bottom layer tiles
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
	//Top layer tiles
	for (int y = 0; y < mMapSizeY; y++)
	{
		mTileTopRow.clear();
		for (int x = 0; x < mMapSizeX; x++)
		{
			inputFile >> input;
			int ID = stoi(input);
			if (ID < 10)
				cout << " " << ID;
			else
				cout << ID;
			cout << " ";
			Tile *tile = new Tile(gridvector(x, y), ID, 0, &textures);
			mTileTopRow.push_back(tile);
		}
		mTopTileLayer.push_back(mTileTopRow);

		cout << endl;
	}
	inputFile >> input;
	int objectNumber;
	objectNumber = stoi(input);
	//Bottom layer objects
	for (int i = 0; i < objectNumber; i++){
		int objectID, xPos, yPos, channel, layer;

		inputFile >> input;
		objectID = stoi(input);

		inputFile >> input;
		xPos = stoi(input);

		inputFile >> input;
		yPos = stoi(input);

		inputFile >> input;
		channel = stoi(input);

		inputFile >> input;
		layer = stoi(input);


		if (objectID == 1){
			mEntities.push_back(new Button(channel, textures.GetTexture(12), gridvector(xPos, yPos)));
		}
	}

	inputFile >> input;
	objectNumber = stoi(input);
	//Top layer objects
	for (int i = 0; i < objectNumber; i++){
		int objectID, xPos, yPos, channel, layer;

		inputFile >> input;
		objectID = stoi(input);

		inputFile >> input;
		xPos = stoi(input);

		inputFile >> input;
		yPos = stoi(input);

		inputFile >> input;
		channel = stoi(input);

		inputFile >> input;
		layer = stoi(input);


		if (objectID == 0){
			//mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(xPos, yPos), 1));
		}
		if (objectID == 2){
			mEntities.push_back(new Crate(textures.GetTexture(4), gridvector(xPos, yPos), 1));

		}
		if (objectID == 3){
			mEntities.push_back(new Door(channel, gridvector(xPos, yPos), textures.GetTexture(11)));
		}
		if (objectID == 4){
			mEntities.push_back(new Guard(textures.GetTexture(10), gridvector(xPos, yPos), 1, "testAI"));
		}


	}

}