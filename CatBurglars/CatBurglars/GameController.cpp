#include "GameController.h"
#include <fstream>
static string FILENAME = "save.txt";
static string LEVEL = "Level:";
static string COLLECT = "Collectibles:";


static int mLevelProgression;
static int mCollectibles;
static int loadedLevel;
static int loadedCollectibles;

void GameController::load(){
	loadGame();
}
void GameController::save(){
	saveGame();
}
void GameController::loadGame(){

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
void GameController::saveGame(){
	readFile();
	ofstream fileStream(FILENAME);

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
void GameController::addCollectible(){
	mCollectibles += 1;
}
void GameController::nextLevel(){

	//LEVELMANAGER
}