#include "Game.h"
#include "gridvector.h"
#include "Crate.h"

static sf::RenderWindow *window;
static TextureHandler textures;

LevelManager levelM;
Crate *crate;

Game::Game() :
mEntities(),
mCat(),
mController()
{
	//Test for loading in maps
	Level testLevel = Level("test");
	levelM.addLevel(testLevel);

	//Test för channel
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
	mCat = new Cat(textures.GetTexture(10), gridvector(2,2), 1);
	//Stores Entities/objects
	mEntities.push_back(mCat);

	//Creates a crate
	crate = new Crate(textures.GetTexture(4), gridvector(1, 1), 1);
	mEntities.push_back(crate);

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

		//Test för Channel
		// Uppdaterar timers för alla kanaler
		Channels::update();

		// Kollar om en kanal är aktiv.
		if (Channels::isChannelActive(1)) {

			// Gör saker sålänge den är aktiv
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

	for each (GameObject *gameObject in mEntities)
	{
		if (Cat * cat = dynamic_cast<Cat*>(gameObject)){
			mController.move(cat);
			cat->Update();
		}
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