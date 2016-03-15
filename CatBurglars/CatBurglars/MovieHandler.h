#pragma once

#include <sfeMovie\Movie.hpp>

class MovieHandler {
public:
	MovieHandler();
	~MovieHandler();
	static void Initialize();
	void PlayMovie(int ID);
	sfe::Movie* getMovie(int ID);
private:
};