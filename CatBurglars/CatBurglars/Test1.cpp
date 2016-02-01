#include "Test1.h"

Test1::Test1() : Test(){

}

Test1::~Test1(){

}

int Test1::getInt(){
	return mInt;
}

void Test1::setInt(int x){
	mInt = x;
}

void Test1::Render(sf::RenderWindow *mainWindow){

}

void Test1::Update(){

}

sf::Vector2i Test1::GetPosition(){
	sf::Vector2i a;
	a.x = 1;
	a.y = 2;
	return a;
}