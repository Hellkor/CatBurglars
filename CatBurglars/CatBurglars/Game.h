#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Screens.h"
#include "GameObject.h"
#include "Cat.h"
#include "Controller.h"
#include "TextureHandler.h"
#include "Level.h"
#include "LevelManager.h"
#include "Channel.h"
#include "Channels.h"
#include "MenuSystem.h"
#include "MenuButton.h"
#include "MenuPage.h"

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
	
	EntityVector mEntities;

	MenuSystem MainMenuSystem;

	MenuPage *page1;
	MenuButton *Continue;
	MenuButton *NewGame;
	MenuButton *Options;
	MenuButton *Catopedia;
	MenuButton *Exit;

	MenuPage *page2;
	MenuButton *ToggleFullscreen;
	MenuButton *ToggleSound;
	MenuButton *BackButton;

	
	
	MenuPage *PausePage;
	MenuButton *ResumeButton;
	MenuButton *RestartButton;
	MenuButton *QuitButton;
};

