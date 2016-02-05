#include "Game.h"


static sf::RenderWindow *window;
static TextureHandler textures;

LevelManager levelM;

Game::Game() :
mEntities(),
mCat(),
mController()
{


	//Test for loading in maps
	Level testLevel = Level("test");
	levelM.addLevel(testLevel);

	//Test f�r channel
	Channel c1 = Channel(1);
	Channel c2 = Channel(2);
	Channels::addChannel(c1);
	Channels::addChannel(c2);

	Channels::setActive(1, false, 10);

	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");
	window->setVerticalSyncEnabled(true);
	textures.Initialize();

	//Creates a cat(player)
	mCat = new Cat(textures.GetTexture(10), 50, 50, 1);
	//Stores Entities/objects
	mEntities.push_back(mCat);



}

Game::~Game()
{

}

void Game::Run(){

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		//Test f�r Channel
		// Uppdaterar timers f�r alla kanaler
		Channels::update();

		// Kollar om en kanal �r aktiv.
		if (Channels::isChannelActive(1)) {

			// G�r saker s�l�nge den �r aktiv
			cout << "active" << endl;
		}
		else {
			cout << "deactive" << endl;
		}



		Update();
		Render();
	}
}

void Game::Update(){

	for each (Cat *cat in mEntities)
	{
		//cout << "X : " << cat->GetPosition().x << endl;
		//cout << "Y : " << cat->GetPosition().y << endl << endl;;
		//Enable keyboard for cat
		mController.move(cat);
	}

}

void Game::Render()
{
	/* Make background green for testing
	window->clear(sf::Color(0, 200, 0, 255));*/

	window->clear();
	levelM.render(window);
	//Render all entities into the window
	for each(Entity *entity in mEntities)
	{
		entity->Render(window);
	}
	window->display();
}