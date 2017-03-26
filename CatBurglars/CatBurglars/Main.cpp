#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <Windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	//Start the Game
	Game game;
	game.Run();

	return 0;
}