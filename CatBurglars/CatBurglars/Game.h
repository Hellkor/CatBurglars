#ifndef INCLUDED_GAME
#define INCLUDE_GAME

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Cat.h"
#include "Controller.h"
#include "TextureHandler.h"
#include "Level.h"
#include "LevelManager.h"
#include "Channel.h"
#include "Channels.h"
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Button.hpp>
#include <SFGUI\Window.hpp>
#include <SFGUI\Box.hpp>
#include <SFGUI\Label.hpp>
#include <SFGUI\Desktop.hpp>
#include <SFGUI\Engines\BREW.hpp>
#include <SFGUI\Image.hpp>

class Game
{
public:
	typedef std::vector<Entity*> EntityVector;
	Game();
	~Game();
	void Run();
private:
	void Update(float dt);
	void Render();
	GameObject *mGameObjectives;
	
	sfg::SFGUI sfGUI;

	EntityVector mEntities;
	void OnButtonClick(int id);

	
	sfg::Desktop desktop;
	sf::Clock clock;
};

#endif