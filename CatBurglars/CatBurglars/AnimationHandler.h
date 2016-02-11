#ifndef INCLUDED_ANIMATIONHANDLER
#define INCLUDED_ANIMATIONHANDLER

#include <SFML\Graphics.hpp>

class AnimationHandler {
public:
	AnimationHandler(int x, int y, sf::Sprite *sprite);
	~AnimationHandler();
	void forwardAnimation();
	void backwardsAnimation();
	void leftAnimation();
	void rightAnimation();
	void abilityAnimation();
	void reset(int direction);

	void animation(int y, int frames);

private:
	sf::Sprite *mSprite;
	sf::Texture *mTexture;
	int mX;
	int mSpriteSizeX;
	int mSpriteSizeY;

	sf::Clock mClock;
	sf::Time mTime;
};

#endif