#include "DialogManager.h"
#include <fstream>
#include <iostream>
sf::Texture DIALOG_BOX_TEXTURE;


DialogManager::DialogManager(string filename,TextureHandler *handler, sf::Vector2f position):
	mFilename(filename),
	mCurrentConversationDialogID(-1),
	mTextureHandler(handler),
	mPosition(position){
	DIALOG_BOX_TEXTURE.loadFromFile("Resources/DialogBox.png");
	mDialogBox.setTexture(DIALOG_BOX_TEXTURE);
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	mRenderText.setFont(mFont);
	mRenderText.setCharacterSize(12);
	mRenderText.setColor(sf::Color::White);
	readFile();

	mTextPos = sf::Vector2f(mPosition.x + 128, mPosition.y);
}

void DialogManager::readFile() {
	ifstream inputFile(mFilename +".txt");
	vector<string> text_block;
	string input;
	int ID;

	string Character;
	string Mood;
	
	while (!inputFile.eof()) {
		
		
		inputFile >> input;
		if (input == "ID:") {
			inputFile >> input;
			ID = stoi(input);
			cout << "ID: " << ID << endl;
		}
		inputFile >> input;
		if (input == "CHARACTER:") {
			inputFile >> input;
			Character = input;
			cout << "CHARACTER: " << Character << endl;
		}
		inputFile >> input;
		if (input == "MOOD:") {
			inputFile >> input;
			Mood = input;
			cout << "Mood: " << Mood << endl;
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
			Dialog *dialog = new Dialog(text_block, ID);
			dialog->setCharacter(Character);
			dialog->setMood(Mood);
			mDialogList.push_back(dialog);
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
	
	if (mCurrentConversationDialogID > -1 && mCurrentConversationDialogID <= mNumberOfDialogs) {
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
	
	
	
	mPortrait.setPosition(mPosition);

	if (mShowDialog) {
		mDialogBox.setPosition(mPosition);

		
		for each (sf::Text t in TextRows) {
			t.setFont(mFont);
			t.setCharacterSize(12);
			window->draw(t);
		}
		
		window->draw(mDialogBox);
		window->draw(mPortrait);
		
		
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
	
	
	setPortrait(mDialogList[ID]->getCharacter(), mDialogList[ID]->getMood());
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

void DialogManager::setPortrait(Character character, Mood mood) {
	switch (character) {
	case SOCKS:
		switch (mood) {
			case ANGRY:
				cout << "angry socks" << endl;
				mPortrait.setTexture(*mTextureHandler->GetTexture(25));
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	case SCOOTER:
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	case SNOW:
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	case SHADOW:
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	case ALEX:
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	case DOUGLAS:
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
		}
		break;
	}
}