#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"
#include "MovieHandler.h"




bool Fullscreen = false;

static sf::RenderWindow *window;
static TextureHandler textures;
static MovieHandler moviehandler;

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

enum MenuState {MainMenu,CatopediaState,Controls};
MenuState menuState = MainMenu;

enum CatopediaPage {Start,Socks,Scooter,Shadow,Snow,Alex,Douglas};
CatopediaPage catopediaState = Start;

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
	MovieHandler::Initialize();

	Level *prolog = new Level(1);
	Level *Cutscene1 = new Level(3);
	Level *Level1 = new Level("1_1");
	Level *level2 = new Level("1_2");
	Level *level3 = new Level("1_3");
	Level *level4 = new Level("1_4");
	Level *level5 = new Level("1_5");
	Level *level6 = new Level("1_6");
	Level *level7 = new Level("1_7");
	Level *level8 = new Level("1_8");
	Level *level9 = new Level("1_9");
	Level *level21 = new Level("2_1");
	Level *level22 = new Level("2_2");
	Level *level23 = new Level("2_3");
	Level *level24 = new Level("flee1");
	Level *level25 = new Level("flee2");
	Level *level26 = new Level("flee3");
	Level *epilog = new Level(2);
	
	
	LevelManager::addLevel(prolog);
	LevelManager::addLevel(Cutscene1);
	LevelManager::addLevel(Level1);
	LevelManager::addLevel(level2);
	LevelManager::addLevel(level3);
	LevelManager::addLevel(level4);
	LevelManager::addLevel(level5); 
	LevelManager::addLevel(level6);
	LevelManager::addLevel(level7);
	LevelManager::addLevel(level8);
	LevelManager::addLevel(level9);
	LevelManager::addLevel(level21);
	LevelManager::addLevel(level22);
	LevelManager::addLevel(level23);
	LevelManager::addLevel(level24);
	LevelManager::addLevel(level25);
	LevelManager::addLevel(level26);
	LevelManager::addLevel(epilog);

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
	ControlsButton = new MenuButton();



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
	sf::Texture Controls1;
	sf::Texture Controls2;


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

	Controls1.loadFromFile("Resources/Menu/ControlsO.png");
	Controls2.loadFromFile("Resources/Menu/ControlsN.png");

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

	ControlsButton->setTexture(&Controls1);
	ControlsButton->setTextureSelected(&Controls2);

	page1->addMenuButton(Continue);
	page1->addMenuButton(NewGame);
	page1->addMenuButton(Options);
	page1->addMenuButton(ControlsButton);
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

	BackControls = new MenuButton();
	BackControls->setTexture(&Back);
	BackControls->setTextureSelected(&BackS);
	Controlpage = new MenuPage(sf::Vector2f(GuiView.getCenter().x - (window->getSize().x / 2) + 10 , 910),"Controls");
	Controlpage->addMenuButton(BackControls);
	controlsTexture.loadFromFile("Resources/Menu/CONTROLLERS.png");
	controlsPageSprite.setTexture(controlsTexture);
	controlsPageSprite.setOrigin(controlsTexture.getSize().x / 2, controlsTexture.getSize().y / 2);
	controlsPageSprite.setPosition(GuiView.getCenter());




	CatopediaPage = new MenuPage(sf::Vector2f(GuiView.getCenter().x - (window->getSize().x / 2) + 10, GuiView.getCenter().y - (window->getSize().y / 2) + 10),"Catopedia");
	SnowButton = new MenuButton();
	ShadowButton = new MenuButton();
	ScooterButton = new MenuButton();
	SocksButton = new MenuButton();
	AlexButton = new MenuButton();
	DouglasButton = new MenuButton();
	CatopediaBack = new MenuButton();

	sf::Texture SnowO;
	sf::Texture SnowN;
	sf::Texture ScooterO;
	sf::Texture ScooterN;
	sf::Texture ShadowO;
	sf::Texture ShadowN;
	sf::Texture SocksO;
	sf::Texture SocksN;

	sf::Texture AlexO;
	sf::Texture AlexN;
	sf::Texture DouglasO;
	sf::Texture DouglasN;

	SnowO.loadFromFile("Resources/Menu/SnowO.png");
	SnowN.loadFromFile("Resources/Menu/SnowN.png");
	ScooterO.loadFromFile("Resources/Menu/ScooterO.png");
	ScooterN.loadFromFile("Resources/Menu/ScooterN.png");
	ShadowO.loadFromFile("Resources/Menu/ShadowO.png");
	ShadowN.loadFromFile("Resources/Menu/ShadowN.png");
	SocksO.loadFromFile("Resources/Menu/SocksO.png");
	SocksN.loadFromFile("Resources/Menu/SocksN.png");
	AlexO.loadFromFile("Resources/Menu/AlexO.png");
	AlexN.loadFromFile("Resources/Menu/AlexN.png");
	DouglasO.loadFromFile("Resources/Menu/DouglasO.png");
	DouglasN.loadFromFile("Resources/Menu/DouglasN.png");

	SnowButton->setTexture(&SnowO);
	ScooterButton->setTexture(&ScooterO);
	ShadowButton->setTexture(&ShadowO);
	SocksButton->setTexture(&SocksO);
	CatopediaBack->setTexture(&Back);
	DouglasButton->setTexture(&DouglasO);
	AlexButton->setTexture(&AlexO);

	SnowButton->setTextureSelected(&SnowN);
	ScooterButton->setTextureSelected(&ScooterN);
	ShadowButton->setTextureSelected(&ShadowN);
	SocksButton->setTextureSelected(&SocksN);
	CatopediaBack->setTextureSelected(&BackS);
	DouglasButton->setTextureSelected(&DouglasN);
	AlexButton->setTextureSelected(&AlexN);

	CatopediaPage->addMenuButton(SnowButton);
	CatopediaPage->addMenuButton(ScooterButton);
	CatopediaPage->addMenuButton(ShadowButton);
	CatopediaPage->addMenuButton(SocksButton);
	CatopediaPage->addMenuButton(AlexButton);
	CatopediaPage->addMenuButton(DouglasButton);
	CatopediaPage->addMenuButton(CatopediaBack);

	MainMenuSystem = MenuSystem();

	MainMenuSystem.addPage(Controlpage);
	MainMenuSystem.addPage(page1);
	MainMenuSystem.addPage(page2);
	MainMenuSystem.addPage(PausePage);
	MainMenuSystem.addPage(CatopediaPage);

	MainMenuSystem.setPage("Main");

	

	socksPagesTexture.loadFromFile("Resources/Menu/Catopedia/Socks.png");
	scooterPagesTexture.loadFromFile("Resources/Menu/Catopedia/Scooter.png");
	snowPagesTexture.loadFromFile("Resources/Menu/Catopedia/Snow.png");
	shadowPagesTexture.loadFromFile("Resources/Menu/Catopedia/Shadow.png");
	catopediaStartTexture.loadFromFile("Resources/Menu/Catopedia/Start.png");
	douglasPageTexture.loadFromFile("Resources/Menu/Catopedia/Douglas.png");
	alexPageTexture.loadFromFile("Resources/Menu/Catopedia/Alex.png");

	socksPageSprite.setTexture(socksPagesTexture);
	scooterPageSprite.setTexture(scooterPagesTexture);
	snowPageSprite.setTexture(snowPagesTexture);
	shadowPageSprite.setTexture(shadowPagesTexture);
	catopediaStartSprite.setTexture(catopediaStartTexture);
	douglasPageSprite.setTexture(douglasPageTexture);
	alexPageSprite.setTexture(alexPageTexture);

	socksPageSprite.setOrigin(socksPagesTexture.getSize().x / 2, socksPagesTexture.getSize().y / 2);
	snowPageSprite.setOrigin(snowPagesTexture.getSize().x / 2, snowPagesTexture.getSize().y / 2);
	scooterPageSprite.setOrigin(scooterPagesTexture.getSize().x / 2, scooterPagesTexture.getSize().y / 2);
	shadowPageSprite.setOrigin(shadowPagesTexture.getSize().x / 2, shadowPagesTexture.getSize().y / 2);
	catopediaStartSprite.setOrigin(catopediaStartTexture.getSize().x / 2, catopediaStartTexture.getSize().y / 2);
	douglasPageSprite.setOrigin(douglasPageTexture.getSize().x / 2, douglasPageTexture.getSize().y / 2);
	alexPageSprite.setOrigin(alexPageTexture.getSize().x / 2, alexPageTexture.getSize().y / 2);

	socksPageSprite.setPosition(GuiView.getCenter());
	scooterPageSprite.setPosition(GuiView.getCenter());
	snowPageSprite.setPosition(GuiView.getCenter());
	shadowPageSprite.setPosition(GuiView.getCenter());
	catopediaStartSprite.setPosition(GuiView.getCenter());
	douglasPageSprite.setPosition(GuiView.getCenter());
	alexPageSprite.setPosition(GuiView.getCenter());

	

}

Game::~Game()
{

}



void Game::Run() {
	bool isFocused = true;
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
		window->create(sf::VideoMode(1920, 1080, 32), "Kattjuvar", sf::Style::Fullscreen);
		window->setMouseCursorVisible(false);
	}
	else if (!Fullscreen) {
		window->create(sf::VideoMode(1920, 1080, 32), "Kattjuvar", sf::Style::Close);
		window->setMouseCursorVisible(true);
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
					mSoundHandler.startMusic("Menu");
				}
			}
			
			SPLASH_COLOR = sf::Color(255, 255, 255, SPLASH_ALPHA);
			SPLASH_SPRITE.setColor(SPLASH_COLOR);

			break;
		case Menu:
			
			switch (menuState)
			{
			case MainMenu:
				MainMenuSystem.UpdateNavigation();

				if (NewGame->isButtonPushed()) {
					LevelManager::loadLevel(0);
					mSoundHandler.stopMusic();
					GameState = RunGame;
					
				}
				if (Continue->isButtonPushed()) {
					LevelManager::loadLastSavedLevel();
					mSoundHandler.stopMusic();
					GameState = RunGame;
				}
				if (Options->isButtonPushed()) {
					cout << "Options" << endl;
					MainMenuSystem.setPage("Options");

				}
				if (Catopedia->isButtonPushed()) {
					MainMenuSystem.setPage("Catopedia");
					menuState = CatopediaState;
					catopediaState = Start;
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
				if (ControlsButton->isButtonPushed()) {
					MainMenuSystem.setPage("Controls");
					menuState = Controls;
				}
				

				break;
			case CatopediaState:
				MainMenuSystem.UpdateNavigation();
				if (CatopediaBack->isButtonPushed()) {
					MainMenuSystem.setPage("Main");
					catopediaState = Start;
					menuState = MainMenu;
				}
				if (ShadowButton->isButtonPushed()) {
					catopediaState = Shadow;
				}
				if (SocksButton->isButtonPushed()) {
					catopediaState = Socks;
				}
				if (ScooterButton->isButtonPushed()) {
					catopediaState = Scooter;
				}
				if (SnowButton->isButtonPushed()) {
					catopediaState = Snow;
				}
				if (AlexButton->isButtonPushed()) {
					catopediaState = Alex;
				}
				if (DouglasButton->isButtonPushed()) {
					catopediaState = Douglas;
				}
				break;
			case Controls:
				MainMenuSystem.UpdateNavigation();
				
				if (BackControls->isButtonPushed()) {
					MainMenuSystem.setPage("Main");
					menuState = MainMenu;
				}
				
				
				break;
			default:
				break;
			}
			

			break;


		case RunGame:


			LevelManager::update(dt);

			if (LevelManager::returnToMainMenu()) {
				LevelManager::resetEndGame();
				GameState = Menu;
				menuState = MainMenu;
				MainMenuSystem.setPage("Main");
			}

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
				LevelManager::unloadLevel();
				MainMenuSystem.setPage("Main");
				mSoundHandler.startMusic("Menu");
			}
			break;



	}
	




}

void Game::Render()
{
	window->clear();

	switch (GameState){
	case Splash:
		
		window->setView(GuiView);
		window->draw(SPLASH_SPRITE);
		
		break;
	case Menu:
		switch (menuState)
		{
		case MainMenu:
			window->draw(menuBackgroundSprite);
			window->setView(GuiView);
			MainMenuSystem.render(window);
			break;
		case CatopediaState:
			window->setView(GuiView);
			
			switch (catopediaState)
			{
			case Start:
				window->draw(catopediaStartSprite);
				break;
			case Socks:
				window->draw(socksPageSprite);
				break;
			case Scooter:
				window->draw(scooterPageSprite);
				break;
			case Shadow:
				window->draw(shadowPageSprite);
				break;
			case Snow:
				window->draw(snowPageSprite);
				break;
			case Alex:
				window->draw(alexPageSprite);
				break;
			case Douglas:
				window->draw(douglasPageSprite);
				break;
			default:
				break;
			}
			MainMenuSystem.render(window);
			break;
		case Controls:
			window->draw(controlsPageSprite);
			MainMenuSystem.render(window);
			break;
		default:
			break;
		}
		
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
	
	
	
	window->display();
}