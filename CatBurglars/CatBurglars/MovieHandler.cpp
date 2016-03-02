#include "MovieHandler.h"

MovieHandler::MovieHandler() {

}

MovieHandler::~MovieHandler() {

}

void MovieHandler::Initialize() {
	mMovieTest.openFromFile("Resources/Videos/spacetestSMALL.wmv");
	mMovieTest.fit(0, 0, (float)1280, (float)720);
}

void MovieHandler::PlayMovie(int ID) {
	
	mMovieTest.play();
}

sfe::Movie* MovieHandler::getMovie() {
	return &mMovieTest;
}