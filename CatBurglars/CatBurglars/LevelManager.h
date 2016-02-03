#ifndef INCLUDED_LEVELMANAGER
#define INCLUDED_LEVELMANAGER

#include "Level.h"
class LevelManager{

public:
	LevelManager();
	void addLevel(Level *level);
	void nextLevel();
	void changeLevel(int stage);
	Level getLevel();

	void clearLevels();

	void loadLevel(int level);

	void update(float dt);
	void render(sf::RenderWindow *window);

private:
	

	std::vector<Level*> mLevels;
	Level *mCurrentL;
	int mCurrentLevel;
};
#endif