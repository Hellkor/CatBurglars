#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"
#include "MovieHandler.h"




bool Fullscreen = false;

static sf::RenderWindow *window;
static TextureHandler textures;
MovieHandler moviehandler;

sf::View GuiView;

int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;



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
	sf::Joystick::update();

	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "CatBurglars", sf::Style::Close);
	GuiView.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	//window->setVerticalSyncEnabled(true);
	//window->setFramerateLimit(60);
	SPLASH_SCREEN.loadFromFile("Resources/splash.png");
	SPLASH_SPRITE.setTexture(SPLASH_SCREEN);
	SPLASH_SPRITE.setOrigin(sf::Vector2f(SPLASH_SCREEN.getSize().x/2, SPLASH_SCREEN.getSize().y/2));
	SPLASH_SPRITE.setPosition(GuiView.getCenter());

	menuBackground.loadFromFile("Resources/Menu/background.png");
	menuBackgroundSprite.setTexture(menuBackground);
	menuBackgroundSprite.setOrigin(sf::Vector2f(menuBackground.getSize().x / 2, menuBackground.getSize().y / 2));
	menuBackgroundSprite.setPosition(GuiView.getCenter());

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

	//Level *leveltest = new Level("Pathfind_Test");

	//LevelManager::addLevel(leveltest);

	LevelManager::load();
	//LevelManager::addCollectible();

	//LevelManager::loadLevel(0);
	
	//moviehandler.Initialize();

	
	page1 = new MenuPage(sf::Vector2f(200, 200), "Main");
	Continue = new MenuButton();
	NewGame = new MenuButton();
	Options = new MenuButton();
	Catopedia = new MenuButton();
	Exit = new MenuButton();



	sf::Texture NewGame1;
	sf::Texture NewGame2;
	sf::Texture Continue1;
	sf::Texture Continue2;
	sf::Texture Options1;
	sf::Texture Options2;
	sf::Texture Catopedia1;
	sf::Texture Catopedia2;
	sf::Texture Exit1;
	sf::Texture Exit2;


	NewGame1.loadFromFile("Resources/Menu/NewGameO.png");
	NewGame2.loadFromFile("Resources/Menu/NewGamen.png");

	Continue1.loadFromFile("Resources/Menu/Continue.png");
	Continue2.loadFromFile("Resources/Menu/Continuen.png");

	Options1.loadFromFile("Resources/Menu/OptionsO.png");
	Options2.loadFromFile("Resources/Menu/Optionsn.png");

	Catopedia1.loadFromFile("Resources/Menu/Catopediao.png");
	Catopedia2.loadFromFile("Resources/Menu/CatopediaN.png");

	Exit1.loadFromFile("Resources/Menu/ExitGameO.png");
	Exit2.loadFromFile("Resources/Menu/ExitGamen.png");

	NewGame->setTexture(&NewGame1);
	NewGame->setTextureSelected(&NewGame2);

	Continue->setTexture(&Continue1);
	Continue->setTextureSelected(&Continue2);

	Options->setTexture(&Options1);
	Options->setTextureSelected(&Options2);

	Catopedia->setTexture(&Catopedia1);
	Catopedia->setTextureSelected(&Catopedia2);

	Exit->setTexture(&Exit1);
	Exit->setTextureSelected(&Exit2);

	page1->addMenuButton(Continue);
	page1->addMenuButton(NewGame);
	page1->addMenuButton(Options);
	page1->addMenuButton(Catopedia);
	page1->addMenuButton(Exit);

	page2 = new MenuPage(sf::Vector2f(200, 200), "Options");
	

	ToggleFullscreen = new MenuButton();
	BackButton = new MenuButton();


	

	sf::Texture Fullscreen;
	sf::Texture FullscreenS;
	sf::Texture Back;
	sf::Texture BackS;

	Fullscreen.loadFromFile("Resources/Menu/FullscreenO.png");
	FullscreenS.loadFromFile("Resources/Menu/FullscreenN.png");

	Back.loadFromFile("Resources/Menu/BackO.png");
	BackS.loadFromFile("Resources/Menu/BackN.png");

	ToggleFullscreen->setTexture(&Fullscreen);
	ToggleFullscreen->setTextureSelected(&FullscreenS);


	BackButton->setTexture(&Back);
	BackButton->setTextureSelected(&BackS);

	page2->addMenuButton(ToggleFullscreen);
	page2->addMenuButton(BackButton);


	PausePage = new MenuPage(sf::Vector2f(200, 200), "Pause");
	sf::Texture Resume;
	sf::Texture ResumeS;
	sf::Texture Restart;
	sf::Texture RestartS;
	sf::Texture Quit;
	sf::Texture QuitS;


	ResumeButton = new MenuButton();
	QuitButton = new MenuButton();
	RestartButton = new MenuButton();
	Resume.loadFromFile("Resources/Menu/ResumeO.png");
	ResumeS.loadFromFile("Resources/Menu/ResumeN.png");

	Restart.loadFromFile("Resources/Menu/RestartO.png");
	RestartS.loadFromFile("Resources/Menu/RestartN.png");

	Quit.loadFromFile("Resources/Menu/QuitGameO.png");
	QuitS.loadFromFile("Resources/Menu/QuitGameN.png");

	ResumeButton->setTexture(&Resume);
	ResumeButton->setTextureSelected(&ResumeS);

	RestartButton->setTexture(&Restart);
	RestartButton->setTextureSelected(&RestartS);

	QuitButton->setTexture(&Quit);
	QuitButton->setTextureSelected(&QuitS);

	PausePage->addMenuButton(ResumeButton);
	PausePage->addMenuButton(RestartButton);
	PausePage->addMenuButton(QuitButton);

	MainMenuSystem = MenuSystem();


	MainMenuSystem.addPage(page1);
	MainMenuSystem.addPage(page2);
	MainMenuSystem.addPage(PausePage);

	MainMenuSystem.setPage("Main");

	

}

Game::~Game()
{

}



void Game::Run() {
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
			if (event.type == sf::Event::GainedFocus) {
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

void changeScreenMode() {
	Fullscreen = !Fullscreen;


	if (Fullscreen) {
		window->create(sf::VideoMode(1920, 1080, 32), "MenuTest", sf::Style::Fullscreen);
	}
	else if (!Fullscreen) {
		window->create(sf::VideoMode(1920, 1080, 32), "MenuTest", sf::Style::Close);
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
					
					GameState = Menu;
				}
			}
			
			SPLASH_COLOR = sf::Color(255, 255, 255, SPLASH_ALPHA);
			SPLASH_SPRITE.setColor(SPLASH_COLOR);

			break;
		case Menu:
			MainMenuSystem.UpdateNavigation();

			if (NewGame->isButtonPushed()) {
				LevelManager::loadLevel(0);
				GameState = RunGame;
			}
			if (Continue->isButtonPushed()) {
				LevelManager::loadLastSavedLevel();
				GameState = RunGame;
			}
			if (Options->isButtonPushed()) {
				cout << "Options" << endl;
				MainMenuSystem.setPage("Options");

			}
			if (Catopedia->isButtonPushed()) {
				cout << "Catopedia" << endl;
			}
			if (ToggleFullscreen->isButtonPushed()) {
				changeScreenMode();
			}
			if (BackButton->isButtonPushed()) {
				MainMenuSystem.setPage("Main");
			}
			if (Exit->isButtonPushed()) {
				window->close();
			}
			

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				GameState = Pause;
				MainMenuSystem.setPage("Pause");
			}
			break;
		

			

		case Pause:
			MainMenuSystem.UpdateNavigation();
			if (ResumeButton->isButtonPushed()) {
				GameState = RunGame;
			}
			if (RestartButton->isButtonPushed()) {
				GameState = RunGame;
			    LevelManager::reloadLevel();
			}
			if (QuitButton->isButtonPushed()) {
				GameState = Menu;
				MainMenuSystem.setPage("Main");
			}
			break;



	}
	




}

void Game::Render()
{
	window->clear();
	//window->clear();
	switch (GameState){
	case Splash:
		
		window->setView(GuiView);
		window->draw(SPLASH_SPRITE);
		
		break;
	case Menu:
		window->draw(menuBackgroundSprite);
		window->setView(GuiView);
		MainMenuSystem.render(window);
		break;
		// Main Game Case
	case RunGame:
		LevelManager::render(window);
		break;
	case Pause:
		LevelManager::render(window);
		MainMenuSystem.render(window);
		break;


	}
	

	
	//window->draw(*moviehandler.getMovie());
	window->display();
}