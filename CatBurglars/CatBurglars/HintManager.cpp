#include "HintManager.h"

HintManager::HintManager(string filename)
	: mFilename(filename)
{
	mFont.loadFromFile("Resources/Fonts/arial.ttf");
	mText.setFont(mFont);
	mText.setCharacterSize(24);
	mText.setPosition(200, 400);
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
	string input;
	int ID;

	while (!inputFile.eof())
	{
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
