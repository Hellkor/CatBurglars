#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"
#include "MovieHandler.h"

static sf::RenderWindow *window;
static TextureHandler textures;
MovieHandler moviehandler;

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

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


sf::Sound mSound;

enum GameState_  { Menu, RunGame, Pause };
GameState_ GameState = RunGame;

Game::Game() {
	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CatBurglars", sf::Style::Close);
	
	window->setFramerateLimit(60);
	//Test for loading in maps

	/*Level *Level0 = new Level("1_1");
	Level *level1 = new Level("1_2");
	Level *level2 = new Level("1_3");
	Level *level3 = new Level("1_4");
	Level *level4 = new Level("1_5");
	Level *level5 = new Level("1_6");
	

	LevelManager::addLevel(Level0);
	LevelManager::addLevel(level1);
	LevelManager::addLevel(level2);
	LevelManager::addLevel(level3);
	LevelManager::addLevel(level4); 
	LevelManager::addLevel(level5);*/

	Level *leveltest = new Level("Pathfind_Test");

	LevelManager::addLevel(leveltest);

	LevelManager::load();
	LevelManager::addCollectible();
	LevelManager::save();

	LevelManager::loadLevel(0);
	
	moviehandler.Initialize();

}

Game::~Game()
{

}

void Game::Run(){
	//moviehandler.PlayMovie(0);
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
			LevelManager::update(dt);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
				LevelManager::nextLevel();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
				LevelManager::loadLevel(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				LevelManager::nextLevel();
			}
			break;


		case Pause:
			break;



	}
	




}

void Game::Render()
{
	//window->setView(view1);
	
	window->clear();
	switch (GameState){
	case Menu:
		break;
		// Main Game Case
	case RunGame:
		LevelManager::render(window);
		break;
	case Pause:
		moviehandler.getMovie()->update();
		break;


	}
	

	
	window->draw(*moviehandler.getMovie());
	window->display();
}