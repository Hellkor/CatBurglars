#pragma once
#include "LevelManager.h"


class GameController{
public:
	static void addCollectible();
	static void nextLevel();
	static void load();
	static void save();
private:

	static void loadGame();
	static void saveGame();

	
};