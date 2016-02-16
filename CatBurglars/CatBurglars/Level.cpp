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
#include "SecuCam.h"
#include "EventPad.h"
#include "MultiDoor.h"
#include "Computer.h"
using namespace std;
#include "Controller.h"
Controller controller;
static TextureHandler textures;
static SoundHandler soundhandler;

float LOAD_PROGRESS = 0;

// Skapar en level från en textfil
Level::Level(string filename) :
	mFile(filename),
	mLoaded(false){

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
	for each (Entity *e in mEntities){
		e->Render(window);
	}
		
}

void Level::addPlayer(Cat *cat , int player){
	


}
void Level::update(float dt){
	bool test = false;
	if (mLoaded){
		Channels::update();

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
				for each (Entity *entity in mEntities){

					if (secuCam *cam = dynamic_cast<secuCam*>(entity)){
						if (cam->getIntersection(cat)&& !(cat->getDashing())){
							
							test = true;
						}
					}

				}

			}


		}
	}


	if (test){
		load();
	}

}

void Level::load(){

	mLoaded = false;

	mEntities.clear();
	mBottomTileLayer.clear();
	mTopTileLayer.clear();


	
	Channel c = Channel(1);
	Channels::addChannel(c);
	Channels::addChannel(Channel(2));
	Channels::addChannel(Channel(3));
	Channels::addChannel(Channel(4));
	Channels::addChannel(Channel(5));
	Channels::addChannel(Channel(10));
	soundhandler.startMusic(1);

	mEntities.push_back(new Button(1, textures.GetTexture(12), gridvector(25, 3), false, 10));
	mEntities.push_back(new secuCam(1,gridvector(27,3),textures.GetTexture(13), 2,1));
	mEntities.push_back(new EventPad(WIN, gridvector(4, 4)));

	mEntities.push_back(new MultiDoor(1, 3, gridvector(10, 4), textures.GetTexture(11)));

	mEntities.push_back(new Button(1, textures.GetTexture(12), gridvector(2, 2), false, 10));
	mEntities.push_back(new Button(2, textures.GetTexture(12), gridvector(3, 2), false, 10));
	mEntities.push_back(new Button(3, textures.GetTexture(12), gridvector(4, 2), false, 10));
	mEntities.push_back(new Button(4, textures.GetTexture(12), gridvector(5, 2), false, 10));
	mEntities.push_back(new Button(5, textures.GetTexture(12), gridvector(6, 2), false, 10));
	mEntities.push_back(new Computer(10, textures.GetTexture(13), gridvector(1, 1), false, 5));
	generateLevel(mFile);

	

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
	//Bottom layer tiles
	for (int y = 0; y < mMapSizeY; y++)
	{
		mTileRow.clear();
		for (int x = 0; x < mMapSizeX; x++)
		{
			inputFile >> input;
			int ID = stoi(input);
			
			Tile *tile = new Tile(gridvector( x , y ), ID, 0, &textures);
			mTileRow.push_back(tile);

		}
		mBottomTileLayer.push_back(mTileRow);

	}
	//Top layer tiles
	for (int y = 0; y < mMapSizeY; y++)
	{
		mTileTopRow.clear();
		for (int x = 0; x < mMapSizeX; x++)
		{
			inputFile >> input;
			int ID = stoi(input);
			
			Tile *tile = new Tile(gridvector(x, y), ID, 0, &textures);
			mTileTopRow.push_back(tile);
			
		}
		mTopTileLayer.push_back(mTileTopRow);

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
			mEntities.push_back(new Button(channel, textures.GetTexture(12), gridvector(xPos, yPos),true,10));
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

			mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(xPos, yPos), 1, &soundhandler));

		}
		if (objectID == 2){
			mEntities.push_back(new Crate(textures.GetTexture(4), gridvector(xPos, yPos), 1));

		}
		if (objectID == 3){
			mEntities.push_back(new Door(channel, gridvector(xPos, yPos), textures.GetTexture(11)));

		}
		if (objectID == 4){
			mEntities.push_back(new Guard(textures.GetTexture(5), gridvector(xPos, yPos), 1, "testAI"));
		}


	}
	

	
	mLoaded = true;

}