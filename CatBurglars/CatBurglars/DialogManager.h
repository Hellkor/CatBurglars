#pragma once
#include <SFML\Graphics.hpp>
#include "Dialog.h"
#include <string>
#include "TextureHandler.h"
using namespace std;
typedef vector<Dialog*> DialogList;

class DialogManager {
public:
	DialogManager(string filename,TextureHandler *handler, sf::Vector2f resolution);
	void showDialog(int ID, float time_In_Sec);
	void startConversation(int ID, int dialogs, float time_in_sec);
	void update();
	void render(sf::RenderWindow *window,sf::View view);
	void setPosition(sf::Vector2f v);
	bool isDialogActive();

	void nextDialog();
	void setSkipText(string skipkey);

	void initialize(sf::View view);
private:
	TextureHandler *mTextureHandler;
	void setPortrait(Character character, Mood mood);
	void setPortrait2(Character character2, Mood mood2);

	int mSelectedDialog;
	DialogList mDialogList;
	DialogList mConversation;
	int mCurrentConversationDialogID;
	int mNumberOfDialogs;
	void readFile();
	string mFilename;
	sf::Vector2f mPosition;
	sf::Vector2f mTextPos;
	sf::Sprite mDialogBox;
	sf::Font mFont;
	vector<sf::Text> TextRows;
	bool mShowDialog;
	TEXT mText_block;
	string mText_String;
	float mShowTime;

	sf::Clock mClock;
	sf::Time mTimer;

	sf::Sprite mPortrait;
	sf::Sprite mPortrait2;

	SelectedCharacter mHighLighted;

	bool mWin = false;

	string mSkipString;
	sf::Text mSkipText;
};