#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"
#include "MovieHandler.h"

static sf::RenderWindow *window;
static TextureHandler textures;
MovieHandler moviehandler;

sf::View GuiView;

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


sf::Texture SPLASH_SCREEN;
sf::Sprite SPLASH_SPRITE;
sf::Color SPLASH_COLOR;

bool SPLASH_SCREEN_PLAYED = false;
bool SPLASH_FADE_IN = false;
bool SPLASH_FADE_OUT = false;

sf::Clock fadeClock;
sf::Time fadeTime = sf::milliseconds(10);
float SPLASH_ALPHA = 0;

enum GameState_  { Menu, RunGame, Pause , Splash };
GameState_ GameState = Splash;

Game::Game() {
	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CatBurglars", sf::Style::Close);
	GuiView.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	//window->setFramerateLimit(60);
	//window->setVerticalSyncEnabled(true);

	SPLASH_SCREEN.loadFromFile("Resources/splash.png");
	SPLASH_SPRITE.setTexture(SPLASH_SCREEN);
	SPLASH_SPRITE.setOrigin(sf::Vector2f(SPLASH_SCREEN.getSize().x/2, SPLASH_SCREEN.getSize().y/2));
	SPLASH_SPRITE.setPosition(GuiView.getCenter());

	

	TextureHandler::Initialize();
	SoundHandler::Initialize();

	Level *Level0 = new Level("1_1");
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
	LevelManager::addLevel(level5);

	

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
	bool isFocused = true;
	//moviehandler.PlayMovie(0);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			//Pauses the game if not focused
			if (event.type == sf::Event::LostFocus) {
				isFocused = false;
			}
			if(event.type == sf::Event::GainedFocus){
				isFocused = true;
			}
		}
		// Update (the events are handled in the actualizar function)
		loops = 0;

		while (miReloj.getElapsedTime().asMilliseconds() > proximo_tick && loops < MAX_SALTEO_FRAMES) {


			if (isFocused) {
				Update(interpolacion);
			}
			
			proximo_tick += SALTEO_TICKS;
			++loops;

		}

		
		interpolacion = static_cast <float> (miReloj.getElapsedTime().asMilliseconds() + SALTEO_TICKS - proximo_tick) / static_cast <float> (SALTEO_TICKS);

		

		Render();
	}
}

void Game::Update(float dt){
	

	switch (GameState){
		case Splash:
			

			if (!SPLASH_SCREEN_PLAYED && !SPLASH_FADE_IN && !SPLASH_FADE_OUT) {
				SPLASH_FADE_IN = true;
				SPLASH_SCREEN_PLAYED = false;
				fadeClock.restart();
			}
			if (SPLASH_FADE_IN) {
				if (SPLASH_ALPHA < 255) {
					if (fadeClock.getElapsedTime().asMilliseconds() >= fadeTime.asMilliseconds()) {
						if (SPLASH_ALPHA + 255 / 100 <= 255) {
							SPLASH_ALPHA += 255 / 100;
						}
						else {
							SPLASH_ALPHA = 255;
						}
						fadeClock.restart();
					}
				}
				else {
					SPLASH_FADE_IN = false;
					SPLASH_FADE_OUT = true;
					fadeClock.restart();
				}
			}
			if (SPLASH_FADE_OUT) {
				if (SPLASH_ALPHA > 0) {
					if (fadeClock.getElapsedTime().asMilliseconds() >= fadeTime.asMilliseconds()) {
						if (SPLASH_ALPHA - 255 / 100 >= 0) {
							SPLASH_ALPHA -= 255 / 100;
						}
						else {
							SPLASH_ALPHA = 0;
						}
						fadeClock.restart();
					}
				}
				else {
					SPLASH_FADE_OUT = false;
					GameState = RunGame;
				}
			}
			
			SPLASH_COLOR = sf::Color(255, 255, 255, SPLASH_ALPHA);
			SPLASH_SPRITE.setColor(SPLASH_COLOR);

			break;
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
	
	//window->clear();
	switch (GameState){
	case Splash:
		window->clear();
		window->setView(GuiView);
		window->draw(SPLASH_SPRITE);
		
		break;
	case Menu:
		window->setView(GuiView);
		break;
		// Main Game Case
	case RunGame:
		window->clear();
		LevelManager::render(window);
		break;
	case Pause:
		moviehandler.getMovie()->update();
		break;


	}
	

	
	window->draw(*moviehandler.getMovie());
	window->display();
}