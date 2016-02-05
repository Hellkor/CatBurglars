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
	Cat *mCat;
	Controller mController;
	LevelManager levelM;

	EntityVector mEntities;
};

#endif