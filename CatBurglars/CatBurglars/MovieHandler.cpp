#include "MovieHandler.h"

static sfe::Movie mProlog, mEpilog,
				  Cutscene1,Cutscene2,Cutscene3,
				efter23,efter22,efter17,efter16;

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
	efter23.openFromFile("Resources/Videos/efter23.mp4");
	efter22.openFromFile("Resources/Videos/efter22.mp4");
	efter17.openFromFile("Resources/Videos/efter17.mp4");
	efter16.openFromFile("Resources/Videos/efter16.mp4");
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
	if (ID == 6)
		efter16.play();
	if (ID == 7)
		efter17.play();
	if (ID == 8)
		efter22.play();
	if (ID == 9)
		efter23.play();
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
	if (ID == 6)
		return &efter16;
	if (ID == 7)
		return &efter17;
	if (ID == 8)
		return &efter22;
	if (ID == 9)
		return &efter23;
}