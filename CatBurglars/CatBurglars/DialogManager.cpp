#include "DialogManager.h"
#include <fstream>
#include <iostream>
sf::Texture DIALOG_BOX_TEXTURE;


DialogManager::DialogManager(string filename,TextureHandler handler):
	mFilename(filename),
	mPosition(300,500),
	mCurrentConversationDialogID(-1){
	DIALOG_BOX_TEXTURE.loadFromFile("Resources/DialogBox.png");
	mDialogBox.setTexture(DIALOG_BOX_TEXTURE);
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	mRenderText.setFont(mFont);
	mRenderText.setCharacterSize(12);
	mRenderText.setColor(sf::Color::White);
	readFile();
	
}

void DialogManager::readFile() {
	ifstream inputFile(mFilename +".txt");
	vector<string> text_block;
	string input;
	int ID;
	
	while (!inputFile.eof()) {
		
		
		inputFile >> input;
		if (input == "ID:") {
			inputFile >> input;
			ID = stoi(input);
			cout << "ID: " << ID << endl;
		}
		inputFile >> input;
		if (input == "Text:") {
			cout << "Input: text" << endl;
			inputFile >> input;
		}
		if (input == "{") {
			inputFile >> input;
			text_block.push_back(input);
		}
		while (input != "}") {
			inputFile >> input;
			
			if (input != "}") {
				cout << input;
				text_block.push_back(input);
			}
		}
		if (input == "}") {
			cout << endl;
			mDialogList.push_back(new Dialog(text_block, ID));
			text_block.clear();
		}

		/*
		inputFile >> input;
		ID = stoi(input);
		inputFile >> input;
		if (input == "{") {
			//continue;
		}
		else break;
		//inputFile >> input;
		while (input != "}") {
			inputFile >> input;
			if (input != "}") {
				text_block.push_back(input);
			}
		}
		if (input == "}") {
			mDialogList.push_back(new Dialog(text_block, ID));
		}
		*/
		
	}
	
}
void DialogManager::update() {
	
	if (mClock.getElapsedTime().asSeconds() > mTimer.asSeconds()) {
		mShowDialog = false;
	}
	
	if (mCurrentConversationDialogID >= 0 && mCurrentConversationDialogID <= mNumberOfDialogs) {
		if (!mShowDialog) {
			showDialog(mCurrentConversationDialogID, 4);
			cout << "add" << endl;
			mCurrentConversationDialogID += 1;
		}
	}
	else {
		mCurrentConversationDialogID = -1;
	}
	
}
void DialogManager::render(sf::RenderWindow *window,sf::Vector2f position) {
	
	mPosition = position;
	mTextPos = sf::Vector2f(mPosition.x + 40, mPosition.y + 10);
	
	if (mShowDialog) {
		mDialogBox.setPosition(mPosition);
		
		for each (sf::Text t in TextRows) {
			t.setFont(mFont);
			t.setCharacterSize(12);
			window->draw(t);
		}
		
		window->draw(mDialogBox);
		
		
	}

	
	
}
void DialogManager::startConversation(int ID,int dialogs,float time_in_seconds) {
	mCurrentConversationDialogID = ID;
	mNumberOfDialogs = dialogs;
}
void DialogManager::showDialog(int ID,float time_as_seconds) {
	TextRows.clear();
	mText_String.clear();
	mText_String = mDialogList[ID]->getString();
	
	cout << mText_String << endl;
	

	int maxcount = 20;
	int charactercount = 0;
	
	sf::Vector2f rowPos = mTextPos;
	string row;
	for (string::size_type i = 0; i < mText_String.size(); i++) {
		row.push_back(mText_String[i]);
		charactercount++;
		
		if (charactercount >= maxcount &&mText_String[i] == ' ') {
	
			sf::Text text;
			text.setString(row);
			rowPos.y += 12;
			text.setPosition(rowPos);
			TextRows.push_back(text);
			charactercount = 0;
			row.clear();
		}
	}
	if (charactercount <= maxcount) {
		sf::Text text;
		text.setString(row);
		rowPos.y += 12;
		text.setPosition(rowPos);
		TextRows.push_back(text);
		charactercount = 0;
		row.clear();
	}
	

	mShowDialog = true;
	mClock.restart();
	mTimer = sf::seconds(time_as_seconds);
}
void DialogManager::setPosition(sf::Vector2f v) {
	mPosition = v;
}

bool DialogManager::isDialogActive() {
	return mShowDialog;
}