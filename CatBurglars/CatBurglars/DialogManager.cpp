#include "DialogManager.h"
#include <fstream>
#include <iostream>
sf::Texture DIALOG_BOX_TEXTURE;

sf::Vector2f PORTRAIT_ONE_POS;
sf::Vector2f PORTRAIT_TWO_POS;


int FONT_SIZE = 16;


DialogManager::DialogManager(string filename,TextureHandler *handler, sf::Vector2f resolution):
	mFilename(filename),
	mCurrentConversationDialogID(-1),
	mTextureHandler(handler){
	DIALOG_BOX_TEXTURE.loadFromFile("Resources/DialogBox.png");
	mDialogBox.setTexture(DIALOG_BOX_TEXTURE);
	
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	
	readFile();

	//setPortrait(SOCKS, ANGRY);
	//setPortrait2(SOCKS, ANGRY);
	
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

	bool win = false;

	SelectedCharacter highlighted;
	
	while (!inputFile.eof()) {
		
		
		inputFile >> input;
		if (input == "ID:") {
			inputFile >> input;
			ID = stoi(input);
		}
		inputFile >> input;
		if (input == "CHARACTER:") {
			inputFile >> input;
			Character = input;
		}
		inputFile >> input;
		if (input == "MOOD:") {
			inputFile >> input;
			Mood = input;
		}
		inputFile >> input;
		if (input == "CHARACTER2:") {
			inputFile >> input;
			Character2 = input;
		}
		inputFile >> input;
		if (input == "MOOD2:") {
			inputFile >> input;
			Mood2 = input;
		}
		inputFile >> input;
		if (input == "WIN:") {
			inputFile >> input;
			if (input == "TRUE") {
				win = true;
			}
			else if (input == "FALSE") {
				win = false;
			}
		}
		inputFile >> input;
		if (input == "Text(1):") {
			highlighted = ONE;
		}
		else if (input == "Text(2):") {
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
				text_block.push_back(input);
			}
		}
		if (input == "}") {
			Dialog *dialog = new Dialog(text_block, ID);
			dialog->setCharacter(Character);
			dialog->setMood(Mood);
			dialog->setCharacter2(Character2);
			dialog->setMood2(Mood2);
			dialog->setSelectedCharacter(highlighted);
			dialog->setWinDialog(win);
			mDialogList.push_back(dialog);
			text_block.clear();
		}

		
	}
	
}
void DialogManager::update() {
	
	if (mClock.getElapsedTime().asSeconds() > mTimer.asSeconds()) {
		mShowDialog = false;
	}
	
	if (mCurrentConversationDialogID > -1 && mCurrentConversationDialogID <= mNumberOfDialogs) {
		if (!mShowDialog) {
			showDialog(mCurrentConversationDialogID, 4);
			
			mCurrentConversationDialogID += 1;
		}
	}
	else {
		if (mWin) {
			mWin = false;
			// WIN
		}
		mCurrentConversationDialogID = -1;
	}
	
}
void DialogManager::initialize(sf::View view) { // Initialize portrait and dialogbox positions
	PORTRAIT_ONE_POS = view.getCenter() + sf::Vector2f(-450, 0);
	PORTRAIT_TWO_POS = view.getCenter() + sf::Vector2f(450, 0);

	mDialogBox.setOrigin(sf::Vector2f(mDialogBox.getTexture()->getSize().x / 2, mDialogBox.getTexture()->getSize().y / 2));
	mDialogBox.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y + (view.getCenter().y/2)));
	mTextPos = sf::Vector2f(mDialogBox.getPosition().x + (FONT_SIZE) - ((mDialogBox.getTexture()->getSize().x / 2)),
							mDialogBox.getPosition().y - (mDialogBox.getTexture()->getSize().y / 2));
}
void DialogManager::render(sf::RenderWindow *window,sf::View view) {

	mPortrait.setOrigin(mPortrait.getTexture()->getSize().x / 2, mPortrait.getTexture()->getSize().y / 2);
	mPortrait2.setOrigin(mPortrait2.getTexture()->getSize().x / 2, mPortrait2.getTexture()->getSize().y / 2);
	
	

	if (mShowDialog) {
		sf::RenderTexture rtext;
		rtext.create(200, 200);
		rtext.clear(sf::Color(150, 150, 150, 0));
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f((mPortrait.getTexture()->getSize().x)*4,( mPortrait.getTexture()->getSize().y)*4));
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

		
		window->draw(mDialogBox);
		for each (sf::Text t in TextRows) {
			t.setFont(mFont);
			t.setCharacterSize(FONT_SIZE);
			window->draw(t);
		}
		
		

		
		
		
		
		
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
	
	int maxcount = mDialogBox.getTexture()->getSize().x / (FONT_SIZE / 2);
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
	mWin = mDialogList[ID]->isAWinDialog();
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
		mPortrait.setTexture(*mTextureHandler->GetTexture(25));
		mPortrait.setScale(sf::Vector2f(-1.0f, 1.0f));
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
			case EMBARESSED:
			break;
			case CONFUSED:
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
			case EMBARESSED:
				break;
			case CONFUSED:
				break;
		}
		break;
	case SNOW:
		mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		mPortrait.setTexture(*mTextureHandler->GetTexture(27));
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
			case EMBARESSED:
				break;
			case CONFUSED:
				break;
		}
		break;
	case SHADOW:
		mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		mPortrait.setTexture(*mTextureHandler->GetTexture(26));
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
			case EMBARESSED:
				break;
			case CONFUSED:
				break;
		}
		break;
	case ALEX:
		mPortrait.setTexture(*mTextureHandler->GetTexture(28));
		mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
			case ANGRY:
			break;
			case SAD:
			break;
			case NEUTRAL:
			break;
			case HAPPY:
			break;
			case EMBARESSED:
				break;
			case CONFUSED:
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
			case EMBARESSED:
				break;
			case CONFUSED:
				break;
		}
		break;
	}
}
void DialogManager::setPortrait2(Character character, Mood mood) {
	switch (character) {
	case SOCKS:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(25));
		mPortrait2.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case ANGRY:
			
			break;
		case SAD:
			break;
		case NEUTRAL:
			
			break;
		case HAPPY:
			
			break;
		case EMBARESSED:
			break;
		case CONFUSED:
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
		case EMBARESSED:
			break;
		case CONFUSED:
			break;
		}
		break;
	case SNOW:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(27));
		mPortrait2.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case ANGRY:
			break;
		case SAD:
			break;
		case NEUTRAL:
			break;
		case HAPPY:
			break;
		case EMBARESSED:
			break;
		case CONFUSED:
			break;
		}
		break;
	case SHADOW:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(26));
		mPortrait2.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case ANGRY:
			break;
		case SAD:
			break;
		case NEUTRAL:
			break;
		case HAPPY:
			break;
		case EMBARESSED:
			break;
		case CONFUSED:
			break;
		}
		break;
	case ALEX:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(28));
		mPortrait2.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case ANGRY:
			break;
		case SAD:
			break;
		case NEUTRAL:
			break;
		case HAPPY:
			break;
		case EMBARESSED:
			break;
		case CONFUSED:
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
		case EMBARESSED:
			break;
		case CONFUSED:
			break;
		}
		break;
	}
}