#include "HintManager.h"

HintManager::HintManager(string filename)
	: mFilename(filename)
{
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	mText.setFont(mFont);
	mText.setCharacterSize(24);
	//mText.setColor(sf::Color::Red);
	mText.setOutlineColor(sf::Color::Red);
	mText.setPosition(0, 700);
	
	ReadFile();
}

HintManager::~HintManager()
{

}

void HintManager::ShowHint(int hintID)
{
	mCurrentHintID = hintID;
	mShowHint = true;
}

void HintManager::Update()
{
	mShowHint = false;
}

void HintManager::Render(sf::RenderWindow *window, sf::View view)
{
	if (mShowHint)
	{
		for each (Hint h in mHintVector)
			if (h.ID == mCurrentHintID)
			{
				mText.setString(h.text);
			}
		window->draw(mText);
	}
}

bool HintManager::IsHintActive()
{
	return mShowHint;
}

void HintManager::ReadFile()
{
	ifstream inputFile(mFilename + ".txt");
	
	int ID;

	while (!inputFile.eof())
	{
		string input;
		inputFile >> input;
		Hint hint;
		ID = stoi(input);
		hint.ID = ID;
		inputFile >> input;
		inputFile >> input;
		hint.text = input;
		while (input != "}")
		{
			inputFile >> input;
			if (input != "}")
				hint.text = hint.text + " " + input;
		}
		mHintVector.push_back(hint);
	}
}
