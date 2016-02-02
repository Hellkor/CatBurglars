#include "Game.h"
#include "gridvector.h"


static sf::RenderWindow *window;
static TextureHandler textures;

LevelManager levelM;
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
	
	textures.Initialize();

	//Creates a cat(player)
	mCat = new Cat(textures.GetTexture(10), gridvector(2,2), 1);
	//Stores Entities/objects
	mEntities.push_back(mCat);

	window->setVerticalSyncEnabled(false);

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
		Channels::update();

		// Kollar om en kanal är aktiv.
		if (Channels::isChannelActive(1)) {

			// Gör saker sålänge den är aktiv
			//cout << "active" << endl;
		}
		else {
			//cout << "deactive" << endl;
		}

		Render();
	}
}

void Game::Update(float dt){

	for each (Cat *cat in mEntities)
	{
		//cout << "X : " << cat->GetPosition().x << endl;
		//cout << "Y : " << cat->GetPosition().y << endl << endl;;
		//Enable keyboard for cat
		mController.move(cat);
		cat->Update(dt);

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