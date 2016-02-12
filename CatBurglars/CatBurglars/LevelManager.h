#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
class LevelManager{

public:
	LevelManager();
	void addLevel(Level *level);
	
	Level getLevel();

	void clearLevels();

	void loadLevel(int level);
	void nextLevel();

	void update(float dt);
	void render(sf::RenderWindow *window);

	void addCollectible();
	
	void load();
	void save();

private:
	static void loadGame();
	static void saveGame();

	std::vector<Level*> mLevels;
	int mCurrentLevel;
};
#endif