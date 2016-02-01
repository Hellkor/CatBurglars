#include "Game.h"
#include <iostream>
#include "Test1.h"

static sf::RenderWindow *window;
static TextureHandler textures;

LevelManager levelM;
Test1 *test1;
Test1 *test2;
GameObject *game;

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
	mCat = new Cat(textures.GetTexture(10), 50, 50, 1);
	//Stores Entities/objects
	mEntities.push_back(mCat);

	test1 = new Test1();
	test2 = new Test1();
	test1 = dynamic_cast<Test1*>(test1);
	test1->setInt(99);
	test2->setInt(777);

	mEntities.push_back(test1);
	//mEntities.push_back(test2);


}

Game::~Game()
{
	while (!mEntities.empty()){
		delete mEntities.back();
		mEntities.pop_back();
	}
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

	for each (Test *abc in mEntities)
	{
		//cout << "X : " << cat->GetPosition().x << endl;
		//cout << "Y : " << cat->GetPosition().y << endl << endl;;
		//Enable keyboard for cat
		//mController.move(cat);
		std::cout << abc->getInt() << std::endl;
	}
	//std::cout << test1->getInt() << std::endl;
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