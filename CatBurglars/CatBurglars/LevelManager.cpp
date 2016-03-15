#include "LevelManager.h"
#include <iostream>

#include <fstream>

static string FILENAME = "save.txt";
static string LEVEL = "Level:";
static string COLLECT = "Collectibles:";

static std::vector<Level*> mLevels;

static int mCurrentLevel;
static int mLevelProgression;
static int mCollectibles;
static int loadedLevel;
static int loadedCollectibles;

// Lägger till ny level i hanterarens lista
void LevelManager::addLevel(Level *level){
	mLevels.push_back(level);
	cout << "Added level" << endl;
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
void LevelManager::reloadLevel() {
	mLevels[mCurrentLevel]->load();
}
void LevelManager::loadLastSavedLevel() {
	loadLevel(mLevelProgression);
}
// Byter level till nästa i listan. 
void LevelManager::nextLevel(){
	if (mCurrentLevel != mLevels.size()-1){
		std::cout << "Changing to next level" << std::endl;
		mLevels[mCurrentLevel]->Clear();
		mCurrentLevel++;
		loadLevel(mCurrentLevel);
		
		saveGame();
	}
}

void LevelManager::prevLevel() {
	if (mCurrentLevel != mLevels.size() + 1) {
		std::cout << "Changing to previous level" << std::endl;
		mCurrentLevel--;
		loadLevel(mCurrentLevel);
	}
}


void LevelManager::render(sf::RenderWindow *window){
	mLevels[mCurrentLevel]->render(window);
}



void LevelManager::load(){
	loadGame();
}
void LevelManager::save(){
	saveGame();
}
void LevelManager::loadGame(){

	ifstream fileInput(FILENAME);
	string input;



	while (!fileInput.eof()){
		fileInput >> input;

		if (input == LEVEL){
			fileInput >> input;
			loadedLevel = stoi(input);
			if (loadedLevel > mLevelProgression){
				mLevelProgression = loadedLevel;
			}
		}
		if (input == COLLECT){
			fileInput >> input;
			loadedCollectibles = stoi(input);
			if (loadedCollectibles > mLevelProgression){
				mCollectibles = loadedCollectibles;
			}
		}
	}



	cout << mCollectibles << endl;
	cout << mLevelProgression << endl;



}
void readFile(){
	ifstream fileInput(FILENAME);
	string input;



	while (!fileInput.eof()){
		fileInput >> input;

		if (input == LEVEL){
			fileInput >> input;
			loadedLevel = stoi(input);
		}
		if (input == COLLECT){
			fileInput >> input;
			loadedCollectibles = stoi(input);
		}
	}
}
void LevelManager::saveGame(){
	readFile();
	ofstream fileStream(FILENAME);

	if (mCurrentLevel > mLevelProgression) {
		mLevelProgression = mCurrentLevel;
	}

	if (loadedCollectibles < mCollectibles){
		fileStream << COLLECT;
		fileStream << " ";
		fileStream << mCollectibles;
		fileStream << endl;
	}
	else {
		fileStream << COLLECT;
		fileStream << " ";
		fileStream << loadedCollectibles;
		fileStream << endl;
	}
	if (loadedLevel < mLevelProgression){
		fileStream << LEVEL;
		fileStream << " ";
		fileStream << mLevelProgression;
		fileStream << endl;
	}
	else{
		fileStream << LEVEL;
		fileStream << " ";
		fileStream << loadedLevel;
		fileStream << endl;
	}

}
void LevelManager::addCollectible(){
	mCollectibles += 1;
}