#include "Crate.h"

int INTERACTION_RADIUSS_CRATE = 64;

Crate::Crate(sf::Texture *texture, gridvector position, int ID, SoundHandler *soundhandler, bool movable): GameObject(),
mID(ID),
mCoord(position),
mSoundHandler(soundhandler),
mSolid(true),
mMoveable(movable){

	mSprite.setTexture(*texture, true);
	if (mMoveable) {
		mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	else {
		mSprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
	}

	mPosition = sf::Vector2i(mCoord.x * 64, mCoord.y * 64);
}

Crate::~Crate(){

}

void Crate::Render(sf::RenderWindow *mainWindow){
	mSprite.setPosition((sf::Vector2f)mPosition);
	mainWindow->draw(mSprite);
}
Layer Crate::getLayer() {
	return FRONT;
}
void Crate::Update(float dt){
	if (mMoving){
		if (direction == 4 && mPosition.y != newPos.y) {
			mPosition.y -= 2;
		}
		else if (direction == 3 && mPosition.y != newPos.y) {
			mPosition.y += 2;
		}
		else if (direction == 2 && mPosition.x != newPos.x) {
			mPosition.x -= 2;

		}
		else if (direction == 1 && mPosition.x != newPos.x) {
			mPosition.x += 2;
		}
		else {
			mMoving = false;
			mSolid = true;
			// säkrar att den håller rätt position
			if (direction == 4) {
				mCoord.y--;
				mPosition.y = newPos.y;
			}
			if (direction == 3) {
				mCoord.y++;
				mPosition.y = newPos.y;
			}
			if (direction == 2) {
				mCoord.x--;
				mPosition.x = newPos.x;
			}
			if (direction == 1) {
				mCoord.x++;
				mPosition.x = newPos.x;
			}
		}



	}

}
bool Crate::isSolid(){
	return mSolid;
}

sf::Vector2i Crate::GetPosition(){
	return mPosition;
}

void Crate::moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && mMoveable) {
		if (mGrid.canCrateMove(gridvector(mCoord.x, mCoord.y - 1), tileLayer, Entities)){
			newPos.y = mPosition.y - 64;
			direction = 4;
			c.restart();
			
			mMoving = true;
			mSolid = false;
		}
	}
}
void Crate::moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && mMoveable) {
		if (mGrid.canCrateMove(gridvector(mCoord.x, mCoord.y + 1), tileLayer, Entities)){
			newPos.y = mPosition.y + 64;
			direction = 3;
			c.restart();
			
			mMoving = true;
			mSolid = false;
		}
	}
}
void Crate::moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && mMoveable) {
		if (mGrid.canCrateMove(gridvector(mCoord.x - 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x - 64;
			direction = 2;
			c.restart();
			
			mMoving = true;
			mSolid = false;
		}
	}
}
void Crate::moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities) {
	if (!mMoving && mMoveable) {
		if (mGrid.canCrateMove(gridvector(mCoord.x + 1, mCoord.y), tileLayer, Entities)){
			newPos.x = mPosition.x + 64;
			direction = 1;
			c.restart();
			
			mMoving = true;
			mSolid = false;
		}
	}
}

int lengthCrate(sf::Vector2i v1, sf::Vector2i v2){
	int length;
	int dx = v2.x - v1.x;
	int dy = v2.y - v1.y;

	length = sqrt((dy * dy) + (dx * dx));
	return length;
}

bool Crate::getInteraction(Cat *cat){

	return true;


}

gridvector Crate::getCoords(){
	return mCoord;
}
bool Crate::isInteracting(){
	return true;
}