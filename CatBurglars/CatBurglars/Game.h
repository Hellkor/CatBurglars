#pragma once

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
	MenuButton *ControlsButton;

	MenuPage *page2;
	MenuButton *ToggleFullscreen;
	MenuButton *BackButton;

	
	
	MenuPage *PausePage;
	MenuButton *ResumeButton;
	MenuButton *RestartButton;
	MenuButton *QuitButton;

	sf::Texture menuBackground;
	sf::Sprite menuBackgroundSprite;
	sf::Texture socksPagesTexture;
	sf::Sprite socksPageSprite;
	sf::Texture scooterPagesTexture;
	sf::Sprite scooterPageSprite;
	sf::Texture snowPagesTexture;
	sf::Sprite snowPageSprite;
	sf::Texture shadowPagesTexture;
	sf::Sprite shadowPageSprite;
	sf::Texture douglasPageTexture;
	sf::Sprite douglasPageSprite;
	sf::Texture alexPageTexture;
	sf::Sprite alexPageSprite;

	sf::Texture catopediaStartTexture;
	sf::Sprite catopediaStartSprite;

	MenuPage *Controlpage;
	MenuButton *BackControls;
	sf::Texture controlsTexture;
	sf::Sprite controlsPageSprite;


	MenuPage *CatopediaPage;
	MenuButton *SocksButton;
	MenuButton *ScooterButton;
	MenuButton *SnowButton;
	MenuButton *ShadowButton;
	MenuButton *CatopediaBack;
	MenuButton *DouglasButton;
	MenuButton *AlexButton;


};

