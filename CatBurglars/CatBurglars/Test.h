#ifndef INCLUDED_TEST
#define INCLUDED_TEST

#include "GameObject.h"

class Test : public GameObject
{
public:
	Test();
	~Test();
	virtual int getInt() = 0;
	virtual void setInt(int x) = 0;
private:
};

#endif