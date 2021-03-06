#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
class LevelManager{

public:
	static void addLevel(Level *level);
	

	static void clearLevels();

	static void loadLevel(int level);
	static void nextLevel();
	static void prevLevel();

	static void update(float dt);
	static void render(sf::RenderWindow *window);

	static void addCollectible();
	
	static void load();
	static void save();

	static void loadLastSavedLevel();

	static void reloadLevel();

	static void unloadLevel();

	static bool returnToMainMenu();

	static void resetEndGame();
	
private:
	static void loadGame();
	static void saveGame();

	
};
#endif