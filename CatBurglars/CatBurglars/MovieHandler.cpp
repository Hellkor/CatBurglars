#include "MovieHandler.h"

static sfe::Movie mMovieTest;

MovieHandler::MovieHandler() {

}

MovieHandler::~MovieHandler() {

}

void MovieHandler::Initialize() {
	mMovieTest.openFromFile("Resources/Videos/prolog.wmv");
}

void MovieHandler::PlayMovie(int ID) {
	if(ID == 1)
	mMovieTest.play();
}

sfe::Movie* MovieHandler::getMovie(int ID) {
	if(ID == 1)
	return &mMovieTest;
}