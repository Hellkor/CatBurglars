#include "TextureHandler.h"

TextureHandler::TextureHandler()
{

}

TextureHandler::~TextureHandler()
{

}

//Load textures of the game
void TextureHandler::Initialize()
{
	mTileTexture.loadFromFile("Resources/TileMap.png");
	mCat1Texture.loadFromFile("Resources/shadow_spritesheet.png");
	mCrate.loadFromFile("Resources/Crate.png");
	mButton.loadFromFile("Resources/Button.png");
	mDoor.loadFromFile("Resources/Door.png");
	mGuard.loadFromFile("Resources/vakt_walk_spritesheet.png");
	mArea.loadFromFile("Resources/area.png");
	mCamera.loadFromFile("Resources/camerasheet.png");
	mComputer.loadFromFile("Resources/computer.png");
	mSnow.loadFromFile("Resources/snow_spritesheet.png");
	
}

//Retrun a texture
sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &mTileTexture;
	if (ID == 4)
		return &mCrate;
	if (ID == 5)
		return &mGuard;
	if (ID == 9)
		return &mSnow;
	if (ID == 10)
		return &mCat1Texture;
	if (ID == 11)
		return &mDoor;
	if (ID == 12)
		return &mButton;
	if (ID == 13)
		return &mCamera;
	if (ID == 14)
		return &mComputer;
	if (ID == 99)
		return &mArea;
}