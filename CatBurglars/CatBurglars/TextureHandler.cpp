#include "TextureHandler.h"
#include <string>

std::string PORTRAITS_DIRECTORY = "Resources/Portraits/";

static sf::Texture mTileTexture, mTileTexture2, mPropTileTexture,mMuseumProps, mSidebarTexture, mSelectorTexture, mSaveTexture, mShadow, mCrate, mButton, mDoor, mBars, mGuard,mGuardMuseum,mDouglas, mArea, mCamera, mComputer, mSnow,
mLaserTexture,

mSocksPortrait, mShadowPortrait, mScooterPortrait, mSnowPortrait, mAlexPortrait, mDouglasPortrait, mSocks, mScooter , mCoolDownDash, mThrowObject;

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
	mTileTexture2.loadFromFile("Resources/Tilemap_Museum.png");
	mShadow.loadFromFile("Resources/shadow_spritesheet.png");
	mCrate.loadFromFile("Resources/Crate.png");	
	mButton.loadFromFile("Resources/Button.png");
	mDoor.loadFromFile("Resources/Door.png");
	mBars.loadFromFile("Resources/Bars.png");
	mGuard.loadFromFile("Resources/vakt1.png");
	mGuardMuseum.loadFromFile("Resources/vakt2.png");
	mDouglas.loadFromFile("Resources/Douglas.png");
	mArea.loadFromFile("Resources/area.png");
	mCamera.loadFromFile("Resources/camerasheet.png");
	mComputer.loadFromFile("Resources/computer.png");
	mSnow.loadFromFile("Resources/snow_spritesheet.png");
	mSocksPortrait.loadFromFile(PORTRAITS_DIRECTORY+  "SocksKon.png");
	mShadowPortrait.loadFromFile(PORTRAITS_DIRECTORY + "ShadowKon.png");
	mSnowPortrait.loadFromFile(PORTRAITS_DIRECTORY + "SnowKon.png");
	mAlexPortrait.loadFromFile(PORTRAITS_DIRECTORY + "AlexKon.png");
	mScooterPortrait.loadFromFile(PORTRAITS_DIRECTORY + "ScooterKon.png");
	mDouglasPortrait.loadFromFile(PORTRAITS_DIRECTORY + "DouglasKon.png");
	mSocks.loadFromFile("Resources/socks_spritesheet.png");
	mScooter.loadFromFile("Resources/scooter_spritesheet.png");
	mPropTileTexture.loadFromFile("Resources/tileset_props.png");
	mCoolDownDash.loadFromFile("Resources/cooldownTest.png");
	mThrowObject.loadFromFile("Resources/glodlampa.png");
	mLaserTexture.loadFromFile("Resources/laser.png");
	mMuseumProps.loadFromFile("Resources/museum_props.png");
}

//Retrun a texture
sf::Texture* TextureHandler::GetTexture(int ID)
{
	if (ID == 0)
		return &mTileTexture;
	if (ID == 1)
		return &mPropTileTexture;
	if (ID == 2)
		return &mTileTexture2;
	if (ID == 3)
		return &mMuseumProps;
	if (ID == 4)
		return &mCrate;
	if (ID == 5)
		return &mGuard;
	if (ID == 6)
		return &mGuardMuseum;
	if (ID == 7)
		return &mDouglas;
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
	if (ID == 16)
		return &mSocks;
	if (ID == 17)
		return &mScooter;
	if (ID == 18)
		return &mLaserTexture;
	if (ID == 19)
		return &mThrowObject;
	if (ID == 25)
		return &mSocksPortrait;
	if (ID == 26)
		return &mShadowPortrait;
	if (ID == 27)
		return &mSnowPortrait;
	if (ID == 28)
		return &mScooterPortrait;
	if (ID == 29)
		return &mAlexPortrait;
	if (ID == 30)
		return &mDouglasPortrait;
	if (ID == 50)
		return &mCoolDownDash;
	if (ID == 99)
		return &mArea;
}