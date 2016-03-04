#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <SFML/Graphics.hpp>

class TextureHandler
{
public:
	TextureHandler();
	~TextureHandler();
	void Initialize();
	sf::Texture mTileTexture,mPropTileTexture, mSidebarTexture, mSelectorTexture, mSaveTexture, mCat1Texture, mCrate,mButton,mDoor,mGuard,mArea,mCamera, mComputer,mSnow,
				mSocksPortrait, mShadowPortrait, mScooterPortrait, mSnowPortrait, mAlexPortrait;
	sf::Texture* GetTexture(int ID);
};

#endif