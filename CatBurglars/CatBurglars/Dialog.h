#pragma once
#include <vector>
#include <string>
using namespace std;

typedef vector<string> TEXT;

class Dialog {
public:
	Dialog(TEXT text , int ID);
	TEXT getText();
	string getString();
private:
	int mID;
	TEXT mText;
	string mString;
};