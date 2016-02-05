#include "LevelManager.h"
#include <iostream>

// N�r en manager skapas startar currentlevel p� 0. Allts� f�rsta banan i listan.
LevelManager::LevelManager() :
	mCurrentLevel(0){

	

}
// L�gger till ny level i hanterarens lista
void LevelManager::addLevel(Level *level){
	mLevels.push_back(level);
}
// Rensar bort alla inlagda levels 
void LevelManager::clearLevels(){
	mLevels.clear();
}


/*     SKALL RETURNERA PEKARE TILL DEN AKTUELLA LEVELN // �TKOMST �T ANDRA KLASSER
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

// Byter level till n�sta i listan. 
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
