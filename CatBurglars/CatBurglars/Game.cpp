#include "Game.h"
#include "gridvector.h"
#include "Crate.h"


static sf::RenderWindow *window;
static TextureHandler textures;



// TIME
// Timestep (Constant Game Speed independent of Variable FPS)
sf::Clock miReloj;

const int TICKS_POR_SEGUNDO = 60;
const int SALTEO_TICKS = 1000 / TICKS_POR_SEGUNDO;
const int MAX_SALTEO_FRAMES = 5;

int loops;
float interpolacion;

sf::Int32 proximo_tick = miReloj.getElapsedTime().asMilliseconds();
////////////////////////////////////////////////////////////

Crate *crate;

Game::Game() :
mCat(),
mController(),
levelM(){
	



	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");
	
	textures.Initialize();

	//Creates a cat(player)

	//Stores Entities/objects
	//Test for loading in maps
	Level *testLevel = new Level("snowshadow1");
	Level *level2 = new Level("axel");

	levelM.addLevel(testLevel);
	levelM.addLevel(level2);

	window->setVerticalSyncEnabled(false);


	levelM.loadLevel(0);
	

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

		// Update (the events are handled in the actualizar function)
		loops = 0;

		while (miReloj.getElapsedTime().asMilliseconds() > proximo_tick && loops < MAX_SALTEO_FRAMES) {

			Update(interpolacion);
			
			proximo_tick += SALTEO_TICKS;
			++loops;

		}

		
		interpolacion = static_cast <float> (miReloj.getElapsedTime().asMilliseconds() + SALTEO_TICKS - proximo_tick) / static_cast <float> (SALTEO_TICKS);

		

		// Draw
		//dibujar(window, interpolacion);
		
		//Test för Channel
		// Uppdaterar timers för alla kanaler
		

		Render();
	}
}

void Game::Update(float dt){
	//mController.move(mCat);
	levelM.update(dt);

	/*
	for each (GameObject *gameObject in mEntities)
	{
		//cout << "X : " << cat->GetPosition().x << endl;
		//cout << "Y : " << cat->GetPosition().y << endl << endl;;
		//Enable keyboard for cat
		
		//cat->Update(dt); // Efter axels version
		if (Crate *crate = dynamic_cast<Crate*>(gameObject)){
			crate->getInteraction(mCat);
		}
		for each(Entity *entity in mEntities)
		{
			entity->Update(dt);
		}
		if (Cat * cat = dynamic_cast<Cat*>(gameObject)){
			mController.move(cat);
			//cat->Update(dt);
		}
	}
	*/
}

void Game::Render()
{
	/* Make background green for testing
	window->clear(sf::Color(0, 200, 0, 255));*/

	window->clear();
	levelM.render(window);
	//Render all entities into the window 
	/*
	for each(Entity *entity in mEntities)
	{
		entity->Render(window);
	}
	*/
	window->display();
}