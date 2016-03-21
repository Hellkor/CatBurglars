#include "MovieHandler.h"

static sfe::Movie mProlog, mEpilog,
				  Cutscene1,Cutscene2,Cutscene3;

MovieHandler::MovieHandler() {

}

MovieHandler::~MovieHandler() {

}

void MovieHandler::Initialize() {
	mProlog.openFromFile("Resources/Videos/prolog.wmv");
	mEpilog.openFromFile("Resources/Videos/Epilog.wmv");
	Cutscene1.openFromFile("Resources/Videos/Cutscene_1.mp4");
	Cutscene2.openFromFile("Resources/Videos/Cutscene_2.mp4");
	Cutscene3.openFromFile("Resources/Videos/Cutscene_2.mp4");
}

void MovieHandler::PlayMovie(int ID) {
	if(ID == 1)
		mProlog.play();
	if (ID == 2)
		mEpilog.play();
	if (ID == 3)
		Cutscene1.play();
	if (ID == 4)
		Cutscene2.play();
	if (ID == 5)
		Cutscene3.play();
}

sfe::Movie* MovieHandler::getMovie(int ID) {
	if(ID == 1)
		return &mProlog;
	if (ID == 2)
		return &mEpilog;
	if (ID == 3)
		return &Cutscene1;
	if (ID == 4)
		return &Cutscene2;
	if (ID == 5)
		return &Cutscene3;
}