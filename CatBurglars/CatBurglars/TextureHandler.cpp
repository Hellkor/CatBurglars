#include "TextureHandler.h"
#include <string>

std::string PORTRAITS_DIRECTORY = "Resources/Portraits/";

static sf::Texture mTileTexture, mPropTileTexture, mSidebarTexture, mSelectorTexture, mSaveTexture, mShadow, mCrate, mButton, mDoor, mBars, mGuard, mArea, mCamera, mComputer, mSnow,
mSocksPortrait, mShadowPortrait, mScooterPortrait, mSnowPortrait, mAlexPortrait;

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
	mShadow.loadFromFile("Resources/shadow_spritesheet.png");
	mCrate.loadFromFile("Resources/Crate.png");	
	mButton.loadFromFile("Resources/Button.png");
	mDoor.loadFromFile("Resources/Door.png");
	mBars.loadFromFile("Resources/Bars.png");
	mGuard.loadFromFile("Resources/vakt1.png");
	mArea.loadFromFile("Resources/area.png");
	mCamera.loadFromFile("Resources/camerasheet.png");
	mComputer.loadFromFile("Resources/computer.png");
	mSnow.loadFromFile("Resources/snow_spritesheet.png");
	mSocksPortrait.loadFromFile(PORTRAITS_DIRECTORY+  "Sockskon_neutral.png");
	mShadowPortrait.loadFromFile(PORTRAITS_DIRECTORY + "Shadowkon_neutral.png");
	mSnowPortrait.loadFromFile(PORTRAITS_DIRECTORY + "snowkgoggles_neutral.png");
	mAlexPortrait.loadFromFile(PORTRAITS_DIRECTORY + "Alexkon_neutral.png");
	

	mPropTileTexture.loadFromFile("Resources/tileset_props.png");
	
}

//Retrun a texture
sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &mTileTexture;
	if (ID == 1)
		return &mPropTileTexture;
	if (ID == 4)
		return &mCrate;
	if (ID == 5)
		return &mGuard;
	if (ID == 9)
		return &mSnow;
	if (ID == 10)
		return &mShadow;
	if (ID == 11)
		return &mDoor;
	if (ID == 12)
		return &mButton;
	if (ID == 13)
		return &mCamera;
	if (ID == 14)
		return &mComputer;
	if (ID == 15)
		return &mBars;
	if (ID == 25)
		return &mSocksPortrait;
	if (ID == 26)
		return &mShadowPortrait;
	if (ID == 27)
		return &mSnowPortrait;
	if (ID == 28)
		return &mAlexPortrait;
	if (ID == 99)
		return &mArea;
}