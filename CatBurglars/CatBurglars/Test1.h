#ifndef INCLUDED_TEST1
#define INCLUDED_TEST1

#include "Test.h"

class Test1 : public Test
{
public:
	Test1();
	~Test1();
	virtual int getInt();
	virtual void setInt(int x);
	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update();
	virtual sf::Vector2i GetPosition();
private:
	int mInt;
};

#endif