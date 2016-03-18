#ifndef INCLUDED_GUARD
#define INCLUDED_GUARD

#include <SFML\Graphics.hpp>
#include "GameObject.h"
#include "Grid.h"
#include "AnimationHandler.h"
#include "Soundhandler.h"
#include "Button.h"
#include "Pathfinder.h"
enum GuardType{Normal,Douglas};
struct Command
{
	int xPos;
	int yPos;
	string direction;
	bool temporary;
};

class Guard : public GameObject
{
	typedef vector<Tile*> TileRow;
	typedef vector<TileRow> TileLayer;
public:
	GuardType mGuardType;
	Guard(TextureHandler *textures, gridvector v, int channel,string AIscript, SoundHandler *soundhandler,string directory, string leveltype,GuardType guardtype);
	virtual ~Guard();

	virtual void Render(sf::RenderWindow *mainWindow);
	virtual void Update(float dt);
	virtual sf::Vector2i GetPosition();
	virtual gridvector getCoords();

	void AImovement(TileLayer *tiles, std::vector<Entity*> *entities, Pathfinder *pathfinder);

	bool mInteracting = false;

	virtual bool isInteracting();

	bool isMoving();

	int getDirection();
	virtual Layer getLayer();

	bool getIntersection(GameObject *obj);

	virtual bool isSolid();

	void interaction(Usable *usable);

	void SetDistraction(gridvector pos, int distractSeconds, int direction);
	void RemoveTemporaryWaits();

	GuardType getGuardType();

private:
	float mSpeed;
	sf::Sprite mSprite;
	int mID;
	sf::Vector2i mPosition;
	gridvector mCoords;
	sf::Vector2i newPos;
	bool mMoving = false;
	Grid mGrid;

	void UpdateConePos();
	std::vector<gridvector*> mVision;
	int mRange;
	int direction = 1;
	int width;
	string mFace;
	sf::Sprite mHitboxSprite;

	void setVision(string face, TileLayer *tiles, std::vector<Entity*> *entities);

	sf::Clock mClock;
	sf::Time mWait;
	int mQueuePos;

	string mAIfile;
	string mDirectory;

	void loadAI(string filename);
	Command mCurrentCommand;
	std::vector<Command> mCommandQueue;

	void moveForward(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveBackWards(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveLeft(TileLayer *tileLayer, std::vector<Entity*> *Entities);
	void moveRight(TileLayer *tileLayer, std::vector<Entity*> *Entities);

	AnimationHandler mAnimationhandler;
	SoundHandler* mSoundHandler;

	sf::Sound mWalkSound;

	Pathfinder *mPathfinder;
};

#endif