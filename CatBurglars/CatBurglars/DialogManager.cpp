#include "DialogManager.h"
#include <fstream>
#include <iostream>
sf::Texture DIALOG_BOX_TEXTURE;

sf::Vector2f PORTRAIT_ONE_POS;
sf::Vector2f PORTRAIT_TWO_POS;

sf::Vector2f PORTRAIT_SIZE = sf::Vector2f(200, 200);

int FONT_SIZE = 24;


DialogManager::DialogManager(string filename,TextureHandler *handler, sf::Vector2f resolution):
	mFilename(filename),
	mCurrentConversationDialogID(-1),
	mTextureHandler(handler){
	DIALOG_BOX_TEXTURE.loadFromFile("Resources/DialogBox.png");
	mDialogBox.setTexture(DIALOG_BOX_TEXTURE);
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	
	readFile();




	mTextPos = sf::Vector2f(resolution.x/2,resolution.y - 100);
	
}

void DialogManager::readFile() {
	ifstream inputFile(mFilename +".txt");
	vector<string> text_block;
	string input;
	int ID;

	string Character;
	string Mood;

	string Character2;
	string Mood2;

	SelectedCharacter highlighted;
	
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
		if (input == "CHARACTER2:") {
			inputFile >> input;
			Character2 = input;
			cout << "CHARACTER2: " << Character2 << endl;
		}
		inputFile >> input;
		if (input == "MOOD2:") {
			inputFile >> input;
			Mood2 = input;
			cout << "Mood2: " << Mood2 << endl;
		}
		inputFile >> input;
		if (input == "Text(1):") {
			cout << "Input: text" << endl;
			highlighted = ONE;
		}
		else if (input == "Text(2):") {
			cout << "Input: text" << endl;
			highlighted = TWO;
		}
		inputFile >> input;
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
			dialog->setCharacter2(Character2);
			dialog->setMood2(Mood2);
			dialog->setSelectedCharacter(highlighted);
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
void DialogManager::render(sf::RenderWindow *window,sf::View view) {

	mPortrait.setOrigin(mPortrait.getTexture()->getSize().x / 2, mPortrait.getTexture()->getSize().y / 2);
	mPortrait2.setOrigin(mPortrait2.getTexture()->getSize().x / 2, mPortrait2.getTexture()->getSize().y / 2);
	
	PORTRAIT_ONE_POS = view.getCenter() + sf::Vector2f(-350,0);
	PORTRAIT_TWO_POS = view.getCenter() + sf::Vector2f(350, 0);
	

	if (mShowDialog) {
		sf::RenderTexture rtext;
		rtext.create(200, 200);
		rtext.clear(sf::Color(150, 150, 150, 0));
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(mPortrait.getTexture()->getSize().x, mPortrait.getTexture()->getSize().y));
		rect.setTexture(&rtext.getTexture());


		rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);

		mPortrait.setPosition(PORTRAIT_ONE_POS);
		mPortrait2.setPosition(PORTRAIT_TWO_POS);

		switch (mHighLighted)
		{
		case ONE:
			
			window->draw(mPortrait2);
			rect.setPosition(mPortrait2.getPosition());
			window->draw(rect, sf::BlendMultiply);
			window->draw(mPortrait);
			break;
		case TWO:
			window->draw(mPortrait);
			rect.setPosition(mPortrait.getPosition());
			window->draw(rect, sf::BlendMultiply);
			window->draw(mPortrait2);
			break;
		default:
			break;
		}

		mDialogBox.setPosition(mPosition);

		
		for each (sf::Text t in TextRows) {
			t.setFont(mFont);
			t.setCharacterSize(FONT_SIZE);
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
			rowPos.y += FONT_SIZE;
			text.setPosition(rowPos);
			TextRows.push_back(text);
			charactercount = 0;
			row.clear();
		}
	}
	if (charactercount <= maxcount) {
		sf::Text text;
		text.setString(row);
		rowPos.y += FONT_SIZE;
		text.setPosition(rowPos);
		TextRows.push_back(text);
		charactercount = 0;
		row.clear();
	}
	
	mHighLighted = mDialogList[ID]->getSelectedCharacter();
	
	setPortrait(mDialogList[ID]->getCharacter(), mDialogList[ID]->getMood());
	setPortrait2(mDialogList[ID]->getCharacter2(), mDialogList[ID]->getMood2());
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
				mPortrait.setScale(sf::Vector2f(-1.0f,-1.0f));
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
void DialogManager::setPortrait2(Character character, Mood mood) {
	switch (character) {
	case SOCKS:
		switch (mood) {
		case ANGRY:
			mPortrait2.setTexture(*mTextureHandler->GetTexture(25));
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