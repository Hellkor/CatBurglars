#include "Game.h"
#include "gridvector.h"
#include "Crate.h"
#include <SFML\Audio.hpp>
#include "Soundhandler.h"


static sf::RenderWindow *window;
static TextureHandler textures;

sf::View MainguiView;
sf::View view1;

sf::Texture MenuBackGround;
sf::Sprite backgroundSprite;

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

sf::Event event;
sf::Sound mSound;

enum GameState_  { Menu, RunGame, Pause };
GameState_ GameState = Menu;

Game::Game() {
	//Creates the main window
	window = new sf::RenderWindow(sf::VideoMode(1024, 720), "CatBurglars");

	//Test for loading in maps

	
	Level *testLevel = new Level("11");
	Level *level2 = new Level("12");

	LevelManager::addLevel(testLevel);
	LevelManager::addLevel(level2);

    window->setFramerateLimit(60);

	LevelManager::load();
	LevelManager::addCollectible();
	LevelManager::save();

	LevelManager::loadLevel(1);
	
	// Initialize main View
	view1.setSize(1024, 720);
	view1.setViewport(sf::FloatRect(0, 0, 1, 1));
	// Initialize GUI View
	MainguiView.setSize(1024, 720);
	MainguiView.setViewport(sf::FloatRect(0, 0, 1, 1));

	MenuBackGround.loadFromFile("Resources/background.png");
	backgroundSprite.setTexture(MenuBackGround);

	//Creating an SF image for the button default
	sf::Image image;
	//Loading the default image for the button
	image.loadFromFile("Resources/image.png");
	//Creating a SFG image using the previous SF image
	
	
	
	
	sfg::Context::Get().GetEngine().SetProperty("Label#button1", "Color", sf::Color(127, 0, 0, 255));

	auto b2 = sfg::Button::Create("Exit Game");
	auto b3 = sfg::Button::Create("Select Stage");

	auto sfgwindow = sfg::Window::Create();
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	auto m_label = sfg::Label::Create("Menu");
	box->Pack(m_label);
	for (int i = 0; i < 10; i++) {
		auto my_button = sfg::Button::Create("Tile: " + std::to_string(i));
		my_button->SetPosition(sf::Vector2f(0, 0));
		auto sgImage = sfg::Image::Create(image);
		my_button->SetImage(sgImage);
		my_button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&Game::OnButtonClick, this, i));
		box->Pack(my_button, false);
	}
    
	sfgwindow->Add(box);
	
	

	
	
	//sfgwindow->SetTitle("Main menu");
	


	desktop.SetProperty("Window > Button#button1", "BackgroundColor", sf::Color::Blue);
	desktop.SetProperty("Button", "BackgroundColor", sf::Color::Blue);
	//desktop.SetProperty("Window > Button", "BackgroundColor", sf::Color::Blue);
	//desktop.SetProperty("Window > Button#button1", "BackgroundColor", sf::Color::Blue);
	desktop.SetProperty("Window", "BackgroundColor", sf::Color::Transparent);
	desktop.Add(sfgwindow);
	
	
}

Game::~Game()
{

}

void Game::OnButtonClick(int id) {
	//GameState = RunGame;
	cout << id;
}
void Game::Run(){
	while (window->isOpen())
	{

		desktop.Update(clock.restart().asSeconds());
		sf::Event event;
		while (window->pollEvent(event))
		{
			desktop.HandleEvent(event);

			// If window is about to be closed, leave program.

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
			break;


		case Pause:


			break;



	}
	




}

void Game::Render()
{
	

	window->clear();
	window->setView(view1);

	switch (GameState){
	
		// Main Game Case
	case RunGame:
		LevelManager::render(window);
		break;
	
	case Menu:
		//LevelManager::render(window);
		window->setView(MainguiView);
		window->draw(backgroundSprite);
		sfGUI.Display(*window);
		break;
		
	case Pause:
		break;


	}
	
	window->display();
}