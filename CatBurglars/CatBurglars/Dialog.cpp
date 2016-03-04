#include "Dialog.h"


Dialog::Dialog(TEXT text, int ID) :
	mText(text),
	mID(ID) {


	int word_per_row;
	for (TEXT::size_type i = 0; i < mText.size(); i++) {
		for (string::size_type j = 0; j < mText[i].size(); j++) {
			mString.push_back(mText[i][j]);
		}
		mString.push_back(' ');
	}
}
TEXT Dialog::getText() {
	return mText;
}
string Dialog::getString() {
	return mString;
}
void Dialog::setMood(string mood) {
	string inputMood = mood;
	for (std::string::size_type i = 0; i < inputMood.size(); i++) {
		char *c = &inputMood[i];
		*c = toupper(*c);
	}
	if (inputMood == "ANGRY") {
		mMood = ANGRY;
	}
	if (inputMood == "SAD") {
		mMood = SAD;
	}
	if (inputMood == "HAPPY") {
		mMood = HAPPY;
	}
	if (inputMood == "NEUTRAL") {
		mMood = NEUTRAL;
	}

}
void Dialog::setWinDialog(bool willWin) {
	mWin = willWin;
}
bool Dialog::isAWinDialog() {
	return mWin;
}
void Dialog::setSelectedCharacter(SelectedCharacter one_or_two) {
	mSelectedCharacter = one_or_two;
}
SelectedCharacter Dialog::getSelectedCharacter() {
	return mSelectedCharacter;
}
Mood Dialog::getMood() {
	return mMood;
}
Character Dialog::getCharacter() {
	return mCharacter;
}
void Dialog::setCharacter(string Character) {
	string inputCharacter = Character;
	for (std::string::size_type i = 0; i < inputCharacter.size(); i++) {
		char *c = &inputCharacter[i];
		*c = toupper(*c);
	}
	if (inputCharacter == "SOCKS") {
		mCharacter = SOCKS;
	}
	if (inputCharacter == "SNOW") {
		mCharacter = SNOW;
	}
	if (inputCharacter == "SCOOTER") {
		mCharacter = SCOOTER;
	}
	if (inputCharacter == "ALEX") {
		mCharacter = ALEX;
	}
	if (inputCharacter == "DOUGLAS") {
		mCharacter = DOUGLAS;
	}
	if (inputCharacter == "SHADOW") {
		mCharacter = SHADOW;
	}
}

void Dialog::setMood2(string mood) {
	string inputMood = mood;
	for (std::string::size_type i = 0; i < inputMood.size(); i++) {
		char *c = &inputMood[i];
		*c = toupper(*c);
	}
	if (inputMood == "ANGRY") {
		mMood2 = ANGRY;
	}
	if (inputMood == "SAD") {
		mMood2 = SAD;
	}
	if (inputMood == "HAPPY") {
		mMood2 = HAPPY;
	}
	if (inputMood == "NEUTRAL") {
		mMood2 = NEUTRAL;
	}

}
Mood Dialog::getMood2() {
	return mMood2;
}
Character Dialog::getCharacter2() {
	return mCharacter2;
}
void Dialog::setCharacter2(string Character) {
	string inputCharacter = Character;
	for (std::string::size_type i = 0; i < inputCharacter.size(); i++) {
		char *c = &inputCharacter[i];
		*c = toupper(*c);
	}
	if (inputCharacter == "SOCKS") {
		mCharacter2 = SOCKS;
	}
	if (inputCharacter == "SNOW") {
		mCharacter2 = SNOW;
	}
	if (inputCharacter == "SCOOTER") {
		mCharacter2 = SCOOTER;
	}
	if (inputCharacter == "ALEX") {
		mCharacter2 = ALEX;
	}
	if (inputCharacter == "DOUGLAS") {
		mCharacter2 = DOUGLAS;
	}
	if (inputCharacter == "SHADOW") {
		mCharacter2 = SHADOW;
	}
}