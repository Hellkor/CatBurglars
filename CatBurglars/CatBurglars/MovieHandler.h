#pragma once

#include <sfeMovie\Movie.hpp>

class MovieHandler {
public:
	MovieHandler();
	~MovieHandler();
	void Initialize();
	void PlayMovie(int ID);
	sfe::Movie* getMovie();
private:
	sfe::Movie mMovieTest;
};