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
	


	

	//Test f�r channel
	Channel c1 = Channel(1);
	Channel c2 = Channel(2);
	Channels::addChannel(c1);
	Channels::addChannel(c2);

	Channels::setActive(1, false, 10);

	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");
	
	textures.Initialize();

	//Creates a cat(player)
	mCat = new Cat(textures.GetTexture(10), gridvector(2,2), 1);
	//Stores Entities/objects
	//Test for loading in maps
	Level *testLevel = new Level("test", mCat, mCat);

	levelM.addLevel(testLevel);
	

	window->setVerticalSyncEnabled(false);

	//Creates a crate
	crate = new Crate(textures.GetTexture(4), gridvector(1, 1), 1);

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
		
		//Test f�r Channel
		// Uppdaterar timers f�r alla kanaler
		Channels::update();

		// Kollar om en kanal �r aktiv.
		if (Channels::isChannelActive(1)) {

			// G�r saker s�l�nge den �r aktiv
			//cout << "active" << endl;
		}
		else {
			//cout << "deactive" << endl;
		}

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

		if (Cat * cat = dynamic_cast<Cat*>(gameObject)){
			mController.move(cat);
			cat->Update(dt);
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