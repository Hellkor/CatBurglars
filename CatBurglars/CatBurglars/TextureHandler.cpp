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
	mSidebarTexture.loadFromFile("Resources/SideBar.png");
	mSelectorTexture.loadFromFile("Resources/Selector.png");
	mSaveTexture.loadFromFile("Resources/Save.png");
	mCat1Texture.loadFromFile("Resources/shadow_spritesheet.png");
	mCrate.loadFromFile("Resources/Crate.png");
	mButton.loadFromFile("Resources/Button.png");
	mDoor.loadFromFile("Resources/Door.png");
	mGuard.loadFromFile("Resources/vakt_walk_spritesheet.png");
	mArea.loadFromFile("Resources/area.png");
	mCamera.loadFromFile("Resources/camera.png");
	
	mCrate.setSmooth(true);
}

//Retrun a texture
sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &mTileTexture;
	if (ID == 1)
		return &mSidebarTexture;
	if (ID == 2)
		return &mSelectorTexture;
	if (ID == 3)
		return &mSaveTexture;
	if (ID == 4)
		return &mCrate;
	if (ID == 5)
		return &mGuard;
	if (ID == 10)
		return &mCat1Texture;
	if (ID == 11)
		return &mDoor;
	if (ID == 12)
		return &mButton;
	if (ID == 13)
		return &mCamera;
	if (ID == 99)
		return &mArea;

}
