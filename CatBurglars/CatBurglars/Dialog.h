#pragma once
#include <vector>
#include <string>
using namespace std;

typedef vector<string> TEXT;
enum Mood {NEUTRAL,ANGRY,HAPPY,PANICKED,RESOLUTE,CONFUSED,LAUGHING,SAD,THINKING,SMIRK,PAPER,KEY,PANTING, EMBARESSED,WORRIED,SIGH,CRYING};
enum Character {SOCKS,SNOW,SHADOW,SCOOTER,ALEX,DOUGLAS};
enum SelectedCharacter {ONE,TWO};

class Dialog {
public:
	Dialog(TEXT text , int ID);
	TEXT getText();
	string getString();

	void setMood(string mood);
	void setCharacter(string Character);
	Mood getMood();
	Character getCharacter();

	void setMood2(string mood);
	void setCharacter2(string Character);
	Mood getMood2();
	Character getCharacter2();

	void setSelectedCharacter(SelectedCharacter one_or_two);
	SelectedCharacter getSelectedCharacter();

	void setWinDialog(bool willWin);
	bool isAWinDialog();
private:
	SelectedCharacter mSelectedCharacter;

	Mood mMood;
	Character mCharacter;

	Mood mMood2;
	Character mCharacter2;

	int mID;
	TEXT mText;
	string mString;

	bool mWin;
};