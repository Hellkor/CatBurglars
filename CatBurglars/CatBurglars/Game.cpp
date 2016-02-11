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

enum GameState_  { Menu, RunGame, Pause };
GameState_ GameState = RunGame;

Game::Game() :
mCat(),
mController(),
levelM(){
	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");

	//Test for loading in maps
	Level *testLevel = new Level("mapmapmap");
	Level *level2 = new Level("level2");
	Level *level3 = new Level("level2");
	Level *level4 = new Level("level2");

	levelM.addLevel(testLevel);
	levelM.addLevel(level2);
	levelM.addLevel(level3);
	levelM.addLevel(level4);

	window->setVerticalSyncEnabled(true);


	levelM.load();
	levelM.addCollectible();
	levelM.save();

	levelM.loadLevel(0);
	


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

		

		Render();
	}
}

void Game::Update(float dt){
	

	switch (GameState){
		case Menu:
			break;


		case RunGame:
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
				levelM.nextLevel();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
				levelM.loadLevel(0);
			}
			break;


		case Pause:
			break;



	}
	




}

void Game::Render()
{
	window->setView(view1);

	window->clear();
	switch (GameState){
	case Menu:
		break;
		// Main Game Case
	case RunGame:
		levelM.render(window);
		break;
	case Pause:
		break;


	}
	

	

	window->display();
}