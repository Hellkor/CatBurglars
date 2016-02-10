#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"

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

sf::View view1(sf::FloatRect(0, 0, 1024, 720));



sf::Sound mSound;

Game::Game() :
mCat(),
mController(),
levelM(){

	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");

	//Test for loading in maps
	Level *testLevel = new Level("testmap");
	Level *level2 = new Level("axel");

	levelM.addLevel(testLevel);
	levelM.addLevel(level2);

	window->setVerticalSyncEnabled(true);

	levelM.loadLevel(0);
	
	//soundhandler.Initialize();
	//soundhandler.startMusic(1);
	//mSound.setBuffer(*soundhandler.GetSound(1));
	view1.setCenter(sf::Vector2f(512, 360));
	view1.setViewport(sf::FloatRect(0, 0, 1, 1));

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		view1.move(0, 2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		view1.move(0, -2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		view1.move(-2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		view1.move(2, 0);
	}

}

void Game::Render()
{
	
	window->setView(view1);
	
	window->clear();

	levelM.render(window);

	window->display();
}