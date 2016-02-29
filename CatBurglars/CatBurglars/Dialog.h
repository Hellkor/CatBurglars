#pragma once
#include <vector>
#include <string>
using namespace std;

typedef vector<string> TEXT;
enum Mood {ANGRY,SAD,HAPPY,NEUTRAL};
enum Character {SOCKS,SNOW,SHADOW,SCOOTER,ALEX,DOUGLAS};

class Dialog {
public:
	Dialog(TEXT text , int ID);
	TEXT getText();
	string getString();

	void setMood(string mood);
	void setCharacter(string Character);
	Mood getMood();
	Character getCharacter();
private:


	Mood mMood;
	Character mCharacter;
	int mID;
	TEXT mText;
	string mString;
};