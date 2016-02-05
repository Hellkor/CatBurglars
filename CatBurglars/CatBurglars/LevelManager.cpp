#include "LevelManager.h"
#include <iostream>

// När en manager skapas startar currentlevel på 0. Alltså första banan i listan.
LevelManager::LevelManager() :
	mCurrentLevel(0){

	

}
// Lägger till ny level i hanterarens lista
void LevelManager::addLevel(Level *level){
	mLevels.push_back(level);
}
// Rensar bort alla inlagda levels 
void LevelManager::clearLevels(){
	mLevels.clear();
}


/*     SKALL RETURNERA PEKARE TILL DEN AKTUELLA LEVELN // ÅTKOMST ÅT ANDRA KLASSER
Level LevelManager::getLevel(){
	Level *level = mLevels[mCurrentLevel];
	return level;
}
*/

void LevelManager::update(float dt){

	mLevels[mCurrentLevel]->update(dt);

}

void LevelManager::loadLevel(int i){

	mCurrentLevel = i;
	mLevels[mCurrentLevel]->load();

}

// Byter level till nästa i listan. 
void LevelManager::nextLevel(){
	if (mCurrentLevel != mLevels.size()-1){
		std::cout << "Changing to next level" << std::endl;
		mCurrentLevel++;
		loadLevel(mCurrentLevel);
		
		
	}
}


void LevelManager::render(sf::RenderWindow *window){
	mLevels[mCurrentLevel]->render(window);
}
