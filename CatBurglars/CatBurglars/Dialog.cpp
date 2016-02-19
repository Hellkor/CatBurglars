#include "Dialog.h"


Dialog::Dialog(TEXT text, int ID) :
	mText(text),
	mID(ID) {


	int word_per_row;
	for (TEXT::size_type i = 0; i < mText.size(); i++) {
		for (string::size_type j = 0; j < mText[i].size(); j++) {
			mString.push_back(mText[i][j]);
		}
		mString.push_back(' ');
	}
}
TEXT Dialog::getText() {
	return mText;
}
string Dialog::getString() {
	return mString;
}