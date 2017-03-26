#include "DialogManager.h"
#include <fstream>
#include <iostream>
#include "LevelManager.h"
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
	mSkipText.setFont(mFont);
	mSkipText.setCharacterSize(24);
	readFile();
	
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
void DialogManager::nextDialog() {
	mShowDialog = false;
}
void DialogManager::setSkipText(string skipkey) {
	mSkipString = skipkey;
}
void DialogManager::update() {
	
	
	if (mCurrentConversationDialogID > -1 && mCurrentConversationDialogID <= mNumberOfDialogs) {
		if (!mShowDialog) {
			showDialog(mCurrentConversationDialogID, 4);
			
			mCurrentConversationDialogID += 1;
		}
	}
	else {
		if (mWin) {
			LevelManager::nextLevel();
			mShowDialog = false;
			mWin = false;
		}
		mCurrentConversationDialogID = -1;
	}
	
}
void DialogManager::initialize(sf::View view) { // Initialize portrait and dialogbox positions
	PORTRAIT_ONE_POS = view.getCenter() + sf::Vector2f(-450, 0);
	PORTRAIT_TWO_POS = view.getCenter() + sf::Vector2f( 450, 0);

	mDialogBox.setOrigin(sf::Vector2f(mDialogBox.getTexture()->getSize().x / 2, mDialogBox.getTexture()->getSize().y / 2));
	mDialogBox.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y + (view.getCenter().y/2)));
	mTextPos = sf::Vector2f(mDialogBox.getPosition().x + (FONT_SIZE) - ((mDialogBox.getTexture()->getSize().x / 2)),
							mDialogBox.getPosition().y - (mDialogBox.getTexture()->getSize().y / 2));
}
void DialogManager::render(sf::RenderWindow *window,sf::View view) {

	mPortrait.setOrigin(mPortrait.getTextureRect().width / 2, mPortrait.getTextureRect().height / 2);
	mPortrait2.setOrigin(mPortrait2.getTextureRect().width / 2, mPortrait2.getTextureRect().height / 2);
	
	

	if (mShowDialog) {
		

		mPortrait.setPosition(PORTRAIT_ONE_POS);
		mPortrait2.setPosition(PORTRAIT_TWO_POS);

		sf::RenderTexture rtext;
		rtext.create(200, 200);
		rtext.clear(sf::Color(150, 150, 150, 0));
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f((mPortrait.getTexture()->getSize().x)* mPortrait.getScale().y, (mPortrait.getTexture()->getSize().y)* mPortrait.getScale().y));
		rect.setTexture(&rtext.getTexture());
		sf::RectangleShape rect2;
		rect2.setSize(sf::Vector2f((mPortrait2.getTexture()->getSize().x) * mPortrait2.getScale().y, (mPortrait2.getTexture()->getSize().y) *mPortrait2.getScale().y));
		rect2.setTexture(&rtext.getTexture());


		rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
		rect2.setOrigin(rect2.getSize().x / 2, rect2.getSize().y / 2);

		rect.setPosition(mPortrait.getPosition());
		rect2.setPosition(mPortrait2.getPosition());

		switch (mHighLighted)
		{
		case ONE:
			
			window->draw(mPortrait2);
			window->draw(rect2, sf::BlendMultiply);
			window->draw(mPortrait);
			break;
		case TWO:
			window->draw(mPortrait);
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
		
	    
		
		string skipstring = "Press: " + mSkipString + " to skip!";
		mSkipText.setPosition(sf::Vector2f((view.getCenter().x)   - (mSkipText.getCharacterSize()* (skipstring.size()/4)),
										   (view.getCenter().y) + ((view.getSize().y/2)-mSkipText.getCharacterSize())));
		mSkipText.setString(skipstring);
		mSkipText.setOutlineColor(sf::Color::Red);
		window->draw(mSkipText);
		
		
		
		
		
	}

	
	
}
void DialogManager::startConversation(int ID,int dialogs,float time_in_seconds) {
	cout << "conversation" << endl;
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
	
	
	
	setPortrait(mDialogList[ID]->getCharacter(), mDialogList[ID]->getMood());
	setPortrait2(mDialogList[ID]->getCharacter2(), mDialogList[ID]->getMood2());
	mHighLighted = mDialogList[ID]->getSelectedCharacter();
	mShowDialog = true;
	mWin = mDialogList[ID]->isAWinDialog();
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
		//mPortrait.setScale(sf::Vector2f(-1.0f, 1.0f));
		switch (mood) {
		case CRYING:
			mPortrait.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		}
		break;
	case SCOOTER:
		mPortrait.setTexture(*mTextureHandler->GetTexture(28));
		break;
	case SNOW:
		mPortrait.setTexture(*mTextureHandler->GetTexture(27));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case WORRIED:
			mPortrait.setTextureRect(sf::IntRect(5 * 320, 0, 320, 180));
			break;
		case SIGH:
			mPortrait.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		}
		break;
	case SHADOW:
		mPortrait.setTexture(*mTextureHandler->GetTexture(26));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case PANTING:
			mPortrait.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		case EMBARESSED:
			mPortrait.setTextureRect(sf::IntRect(7 * 320, 0, 320, 180));
			break;
		}
		break;
	case ALEX:
		mPortrait.setTexture(*mTextureHandler->GetTexture(29));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case SAD:
			mPortrait.setTextureRect(sf::IntRect(7 * 320, 0, 320, 180));
			break;
		case THINKING:
			mPortrait.setTextureRect(sf::IntRect(8 * 320, 0, 320, 180));
			break;
		case SMIRK:
			mPortrait.setTextureRect(sf::IntRect(9 * 320, 0, 320, 180));
			break;
		case PAPER:
			mPortrait.setTextureRect(sf::IntRect(10 * 320, 0, 320, 180));
			break;
		case KEY:
			mPortrait.setTextureRect(sf::IntRect(11 * 320, 0, 320, 180));
			break;
		}
		break;
	case DOUGLAS:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(30));
		break;
	}
	switch (mood) {
	case NEUTRAL:
		mPortrait.setTextureRect(sf::IntRect(0, 0, 320, 180));
		break;
	case ANGRY:
		mPortrait.setTextureRect(sf::IntRect(1 * 320, 0, 320, 180));
		break;
	case HAPPY:
		mPortrait.setTextureRect(sf::IntRect(2 * 320, 0, 320, 180));
		break;
	case PANICKED:
		mPortrait.setTextureRect(sf::IntRect(3 * 320, 0, 320, 180));
		break;
	case RESOLUTE:
		mPortrait.setTextureRect(sf::IntRect(4 * 320, 0, 320, 180));
		break;
	case CONFUSED:
		mPortrait.setTextureRect(sf::IntRect(3 * 320, 0, 320, 180));
		break;
	case LAUGHING:
		mPortrait.setTextureRect(sf::IntRect(5 * 320, 0, 320, 180));
		break;
	}
	mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
}
void DialogManager::setPortrait2(Character character, Mood mood) {
	switch (character) {
	case SOCKS:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(25));
		//mPortrait.setScale(sf::Vector2f(-1.0f, 1.0f));
		switch (mood) {
		case CRYING:
			mPortrait2.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		}
		break;
	case SCOOTER:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(28));
		break;
	case SNOW:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(27));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case WORRIED:
			mPortrait2.setTextureRect(sf::IntRect(5 * 320, 0, 320, 180));
			break;
		case SIGH:
			mPortrait2.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		}
		break;
	case SHADOW:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(26));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case PANTING:
			mPortrait2.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		case EMBARESSED:
			mPortrait2.setTextureRect(sf::IntRect(7 * 320, 0, 320, 180));
			break;
		}
		break;
	case ALEX:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(29));
		//mPortrait.setScale(sf::Vector2f(-4.0f, 4.0f));
		switch (mood) {
		case SAD:
			mPortrait2.setTextureRect(sf::IntRect(6 * 320, 0, 320, 180));
			break;
		case THINKING:
			mPortrait2.setTextureRect(sf::IntRect(7 * 320, 0, 320, 180));
			break;
		case SMIRK:
			mPortrait2.setTextureRect(sf::IntRect(8 * 320, 0, 320, 180));
			break;
		case PAPER:
			mPortrait2.setTextureRect(sf::IntRect(9 * 320, 0, 320, 180));
			break;
		case KEY:
			mPortrait2.setTextureRect(sf::IntRect(10 * 320, 0, 320, 180));
			break;
		}
		break;
	case DOUGLAS:
		mPortrait2.setTexture(*mTextureHandler->GetTexture(30));
		break;
	}
	switch (mood) {
	case NEUTRAL:
		mPortrait2.setTextureRect(sf::IntRect(0, 0, 320, 180));
		break;
	case ANGRY:
		mPortrait2.setTextureRect(sf::IntRect(1 * 320, 0, 320, 180));
		break;
	case HAPPY:
		mPortrait2.setTextureRect(sf::IntRect(2 * 320, 0, 320, 180));
		break;
	case PANICKED:
		mPortrait2.setTextureRect(sf::IntRect(3 * 320, 0, 320, 180));
		break;
	case RESOLUTE:
		mPortrait2.setTextureRect(sf::IntRect(4 * 320, 0, 320, 180));
		break;
	case CONFUSED:
		mPortrait2.setTextureRect(sf::IntRect(3 * 320, 0, 320, 180));
		break;
	case LAUGHING:
		mPortrait2.setTextureRect(sf::IntRect(5 * 320, 0, 320, 180));
		break;
	}
	mPortrait2.setScale(sf::Vector2f(4.0f, 4.0f));
}