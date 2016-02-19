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
#include "Collectible.h"
#include <SFML\Graphics\BlendMode.hpp>;
#include "DialogManager.h"
#include "Controller.h"
using namespace std;

static TextureHandler	textures;
static SoundHandler		soundhandler;

// SPLIT SCREEN BORDER
sf::Texture				DIVIDER_TEXTURE;
sf::Sprite				DIVIDER_SPRITE;
// LOAD PROGRESS
float					LOAD_PROGRESS			=	0;
// FOV LIGHT VARIABLES
sf::Texture				FOV_lightTexture;
sf::Sprite				FOV_light;
sf::RenderTexture		FOV_lightMapTexture;
sf::Sprite				FOV_lightmap;

// LIGHT ENGINE VARIABLES
sf::Texture				lightTexture;
sf::Sprite				light;
sf::RenderTexture		lightMapTexture;
sf::Sprite				lightmap;

// TEST DIALOGMANAGER

DialogManager dialogManager("dialog", textures);

// LIGHT STRUCTURE FOR BOTH LIGHT AND FOV LIGHT
struct Light
{
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Color color;
	Light(sf::Vector2f nposition, sf::Vector2f nscale, sf::Color ncolor) :
		position(nposition),
		scale(nscale),
		color(ncolor)
	{
	}
};

// FOV LIGHTS
Light				*l1		= new Light(sf::Vector2f(0, 0), sf::Vector2f(0.9f, 0.9f), sf::Color(255, 255, 255, 255)); // 255, 180, 130, 255
Light				*l2		= new Light(sf::Vector2f(0, 0), sf::Vector2f(0.9f, 0.9f), sf::Color(255, 255, 255, 255));

std::vector<Light*> lights; // Contains all the lights



// Skapar en level fr�n en textfil
Level::Level(string filename) :
	mFile(filename),
	mLoaded(false),
	p1Controller(Controller(KeyboardOne)),
	p2Controller(Controller(KeyboardTwo)){


	// Initialize GUI View
	guiView.setSize(1024, 720);
	guiView.setViewport(sf::FloatRect(0, 0, 1, 1));

	//Initialize textures
	textures.Initialize();
	soundhandler.Initialize();

	
	

	// FOV LIGHT ------------------------------------------------------------------------------------------------------------------------------------
	FOV_lightMapTexture.create(5000, 5000); // Make a lightmap that can cover our screen
	FOV_lightmap.setTexture(FOV_lightMapTexture.getTexture()); // Make our lightmap sprite use the correct texture


	FOV_lightTexture.loadFromFile("Resources/light.png"); // Load in our light 
	FOV_lightTexture.setSmooth(true); // (Optional) It just smoothes the light out a bit

	FOV_light.setTexture(FOV_lightTexture); // Make our lightsprite use our loaded image
	FOV_light.setTextureRect(sf::IntRect(0, 0, 1024, 1024)); // Set where on the image we will take the sprite (X position, Y position, Width, Height)
	FOV_light.setOrigin(512.f, 512.f); // This will offset where we draw our ligts so the center of the light is right over where we want our light to be

	//--------------------------------------------------------------------------------------------------------------------------------------------
	// LIGHT ------------------------------------------------------------------------------------------------------------------------------------
	lightMapTexture.create(5000, 5000); // Make a lightmap that can cover our screen
	lightmap.setTexture(lightMapTexture.getTexture()); // Make our lightmap sprite use the correct texture


	lightTexture.loadFromFile("Resources/light.png"); // Load in our light 
	lightTexture.setSmooth(true); // (Optional) It just smoothes the light out a bit

	light.setTexture(lightTexture); // Make our lightsprite use our loaded image
	light.setTextureRect(sf::IntRect(0, 0, 1024, 1024)); // Set where on the image we will take the sprite (X position, Y position, Width, Height)
	light.setOrigin(512.f, 512.f); // This will offset where we draw our ligts so the center of the light is right over where we want our light to be

	lights.push_back(new Light(sf::Vector2f(200, 200), sf::Vector2f(0.1f, 0.1f), sf::Color(255, 180, 130, 255)));
	//--------------------------------------------------------------------------------------------------------------------------------------------


	// DIVIDER
	DIVIDER_TEXTURE.loadFromFile("Resources/split_divider.png");
	DIVIDER_SPRITE.setTexture(DIVIDER_TEXTURE);
	DIVIDER_SPRITE.setOrigin(DIVIDER_TEXTURE.getSize().x / 2, DIVIDER_TEXTURE.getSize().y / 2);

	dialogManager.startConversation(0, 1, 5);
	dialogManager.showDialog(1, 10);
	
}

// Renderar level
void Level::render(sf::RenderWindow *window){
	
	window->clear();
	window->setView(mPlayer1View);
	

	for (TileLayer::size_type y = 0; y < mBottomTileLayer.size(); y++)
	{
		for (TileRow::size_type x = 0; x < mBottomTileLayer[y].size(); x++)
		{
			mBottomTileLayer[y][x]->Render(window);
			mTopTileLayer[y][x]->Render(window);
		}
	}
	for each (Entity *e in mEntities){
		if (e->getLayer() == BACK) {
			e->Render(window);
		}
	}
	for each (Entity *e in mEntities) {
		if (e->getLayer() == FRONT) {
			e->Render(window);
		}
	}
	
	renderLight(window);
	renderPlayerFOV(window, 1);
	
	
	if (mPlayers == 2){
		window->setView(mPlayer2View); 
		for (TileLayer::size_type y = 0; y < mBottomTileLayer.size(); y++)
		{
			for (TileRow::size_type x = 0; x < mBottomTileLayer[y].size(); x++)
			{
				mBottomTileLayer[y][x]->Render(window);
				mTopTileLayer[y][x]->Render(window);
			}
		}
		for each (Entity *e in mEntities) {
			if (e->getLayer() == BACK) {
				e->Render(window);
			}
		}
		for each (Entity *e in mEntities) {
			if (e->getLayer() == FRONT) {
				e->Render(window);
			}
		}
		
		renderLight(window);
		renderPlayerFOV(window, 2);

		
		
	}

	// Draw gui objects
	window->setView(guiView);
	if (mPlayers == 2) {
		DIVIDER_SPRITE.setPosition(guiView.getCenter());
		window->draw(DIVIDER_SPRITE);
	}
	
	dialogManager.render(window, sf::Vector2f(5,300));
}

void Level::addPlayer(Cat *cat , int player){
	


}
void Level::update(float dt){
	bool test = false;

	dialogManager.update();

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
				
				if (cat->getPlayerIndex() == 1){
					l1->position.x = cat->GetPosition().x +32;
					l1->position.y = cat->GetPosition().y +32;
					p1Controller.move(cat, &mTopTileLayer, &mEntities);
					mPlayer1View.setCenter((sf::Vector2f)cat->GetPosition());
				}
				if (cat->getPlayerIndex() == 2){
					l2->position.x = cat->GetPosition().x + 32;
					l2->position.y = cat->GetPosition().y + 32;
					p2Controller.move(cat, &mTopTileLayer, &mEntities);
					mPlayer2View.setCenter((sf::Vector2f)cat->GetPosition());
				}
				

				for each (Entity *entity in mEntities){
					//Pick up Collectible
					if (Collectible *collectible = dynamic_cast<Collectible*>(entity)) {
						if (collectible->getInteraction(cat)) {

						}
					}
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
void Level::renderLight(sf::RenderWindow *window) {
	// ------------------------------------------------- Render Light ---------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------------------

	// Clear the buffer where we draw the lights, this color could be changed depending on the time of day in the game to show a night/daytime cycle
	lightMapTexture.clear(sf::Color(150, 150, 150, 0));

	// Loop over the lights in the vector
	for (std::size_t i = 0; i < lights.size(); ++i)
	{
		// Set the attributes of the light sprite to those of the current light
		light.setScale(lights[i]->scale);
		light.setColor(lights[i]->color);
		light.setPosition(lights[i]->position);

		//Draw it to the lightmap
		lightMapTexture.draw(light, sf::BlendAdd); // This blendmode is used so the black in our lightimage won't be drawn to the lightmap
	}
	lightMapTexture.display(); // Need to make sure the rendertexture is displayed
	lightmap.setTextureRect(sf::IntRect(0, 0, 5000, 5000)); // What from the lightmap we will draw
	lightmap.setPosition(0, 0); // Where on the backbuffer we will draw
	window->draw(lightmap, sf::BlendMultiply); // This blendmode is used to add the darkness from the 	
	// ------------------------------------------------- ----------- ---------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------------------
}

void Level::renderPlayerFOV(sf::RenderWindow *window, int player) {
	// Clear the buffer where we draw the lights, this color could be changed depending on the time of day in the game to show a night/daytime cycle
	FOV_lightMapTexture.clear(sf::Color(0, 0, 0, 0));

	
	// Set the attributes of the light sprite to those of the current light
	if (player == 1) {
		FOV_light.setScale(l1->scale);
		FOV_light.setColor(l1->color);
		FOV_light.setPosition(l1->position);
	}
	if (player == 2) {
		FOV_light.setScale(l2->scale);
		FOV_light.setColor(l2->color);
		FOV_light.setPosition(l2->position);
	}

	//Draw it to the lightmap
	FOV_lightMapTexture.draw(FOV_light, sf::BlendAdd); // This blendmode is used so the black in our lightimage won't be drawn to the lightmap
	
	FOV_lightMapTexture.display(); // Need to make sure the rendertexture is displayed
	FOV_lightmap.setTextureRect(sf::IntRect(0, 0, 5000, 5000)); // What from the lightmap we will draw
	FOV_lightmap.setPosition(0, 0); // Where on the backbuffer we will draw
	window->draw(FOV_lightmap, sf::BlendMultiply); // This blendmode is used to add the darkness from the 	
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

	generateLevel(mFile);

	

}
void Level::generateView(){

	if (mPlayers == 1){
		mPlayer1View.setSize(1024, 720);
		mPlayer1View.setViewport(sf::FloatRect(0, 0, 1, 1));
	}
	else if (mPlayers == 2){
		mPlayer1View.setSize(512, 720);
		mPlayer1View.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
		mPlayer2View.setSize(512, 720);
		mPlayer2View.setViewport(sf::FloatRect(0.5, 0, 0.5f, 1));
	}
	


	

}
void Level::updateViews(){
	
}
// Laddar in leveln fr�n sparfilen
void Level::generateLevel(string name){
	mPlayers = 0;
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
			cout << ID << " ";
			Tile *tile = new Tile(gridvector( x , y ), ID, 0, &textures);
			mTileRow.push_back(tile);
			

		}
		cout << endl;
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
			cout << ID << " ";
			if (ID != 24) {
				Tile *tile = new Tile(gridvector(x, y), ID, 0, &textures);
				mTileTopRow.push_back(tile);
			}
			else {
				Tile *tile = new Tile(gridvector(x, y), 0, 0, &textures);
				mTileTopRow.push_back(tile);
			}
			
			
			
		}
		mTopTileLayer.push_back(mTileTopRow);
		cout << endl;
	}
	inputFile >> input;
	int objectNumber;
	objectNumber = stoi(input);
	//Bottom layer objects
	for (int i = 0; i < objectNumber; i++){
		int objectID, xPos, yPos, channel, layer, hold;

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


		inputFile >> input;
		hold = stoi(input);


		if (objectID == 1){
			mEntities.push_back(new Button(channel, textures.GetTexture(12), gridvector(xPos, yPos),false,hold));
		}
		if (objectID == 5) {
			mEntities.push_back(new Button(channel, textures.GetTexture(12), gridvector(xPos, yPos), true, hold));
		}

	}

	inputFile >> input;
	objectNumber = stoi(input);

	int playernum = 0;

	//Top layer objects
	for (int i = 0; i < objectNumber; i++){
		int objectID, xPos, yPos, channel, layer,range;
		string script, facing;

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

		inputFile >> input;
		script = input;

		inputFile >> input;
		facing = input;

		inputFile >> input;
		range = stoi(input);

		if (objectID == 0){
			playernum++;
			if (playernum == 2){
				mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(xPos, yPos), 1, &soundhandler, 2));
			}
			if (playernum == 1){
				mEntities.push_back(new Cat(textures.GetTexture(10), gridvector(xPos, yPos), 1, &soundhandler,1));
				
			}
		}

		if (objectID == 2){
			mEntities.push_back(new Crate(textures.GetTexture(4), gridvector(xPos, yPos), 1));

		}
		if (objectID == 3){
			mEntities.push_back(new Door(channel, gridvector(xPos, yPos), textures.GetTexture(11)));
		}
		if (objectID == 4){
			mEntities.push_back(new Guard(textures.GetTexture(5), gridvector(xPos, yPos), 1, script));
		}
		if (objectID == 6) {
			mEntities.push_back(new secuCam(channel, gridvector(xPos, yPos), textures.GetTexture(13), range, facing));
		}
		if (objectID == 7) {
			mEntities.push_back(new Computer(channel, textures.GetTexture(13), gridvector(xPos, yPos), false, 5));
		}
		if (objectID == 8) {
			mEntities.push_back(new MultiDoor(channel, range, gridvector(xPos, yPos), textures.GetTexture(11)));
		}

	}
	

	mPlayers = playernum;
	generateView();
	mLoaded = true;

}