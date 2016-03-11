#ifndef HINTMANAGER_H
#define HINTMANAGER_H

#include <SFML\Graphics.hpp>
#include <fstream>

using namespace std;

struct Hint
{
	int ID;
	string text;
};

class HintManager
{
public:
	HintManager(string filename);
	~HintManager();
	void ShowHint(int hintID);
	void Update();
	void Render(sf::RenderWindow *window, sf::View view);
	bool IsHintActive();
private:
	string mFilename;
	bool mShowHint;
	void ReadFile();
	sf::Font mFont;
	sf::Text mText;
	vector<Hint> mHintVector;
	int mCurrentHintID;
};

#endif