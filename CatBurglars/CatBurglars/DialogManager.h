#pragma once
#include <SFML\Graphics.hpp>
#include "Dialog.h"
#include <string>
#include "TextureHandler.h"
using namespace std;
typedef vector<Dialog*> DialogList;

class DialogManager {
public:
	DialogManager(string filename,TextureHandler handler);
	void showDialog(int ID, float time_In_Sec);
	void startConversation(int ID, int dialogs, float time_in_sec);
	void update();
	void render(sf::RenderWindow *window,sf::Vector2f position);
	void setPosition(sf::Vector2f v);
private:
	int mSelectedDialog;
	DialogList mDialogList;
	DialogList mConversation;
	int mCurrentConversationDialogID;
	int mNumberOfDialogs;
	void readFile();
	string mFilename;
	sf::Vector2f mPosition;
	sf::Sprite mDialogBox;
	sf::Font mFont;
	sf::Text mRenderText;
	vector<sf::Text> TextRows;
	bool mShowDialog;
	TEXT mText_block;
	string mText_String;
	float mShowTime;

	sf::Clock mClock;
	sf::Time mTimer;
};