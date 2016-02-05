#include "Tile.h"

static const int width = 64, height = 64;
static int selectedID = 0;
static bool changeAllowed = true;
static sf::Texture *texture;
static TextureHandler *textureHandler;

Tile::Tile(gridvector coords, int ID, int textureID, TextureHandler *textures)
: Entity(), mID(ID){

	mPosition.x = coords.x * width;
	mPosition.y = coords.y * height;
	mCoords = gridvector(mCoords.x, mCoords.y);

	textureHandler = textures;
	texture = textureHandler->GetTexture(textureID);
	mSprite.setTexture(*texture, true);
	mSprite.setTextureRect(sf::IntRect((ID % 3) * width, floor(ID / 3) * height, width, height));
}

Tile::~Tile()
{

}

gridvector Tile::getCoords(){
	return mCoords;
}

void Tile::Render(sf::RenderWindow *window)
{
	mSprite.setPosition(mPosition.x, mPosition.y);
	window->draw(mSprite);
}
void Tile::Update(float dt){

}
//Added
sf::Vector2i Tile::GetPosition(){
	return mPosition;
}

sf::Vector2i Tile::GetSize(){ return sf::Vector2i(width, height); }

void Tile::IDChangeInfo(int ID, bool allowed)
{
	selectedID = ID;
	changeAllowed = !allowed;
}


int Tile::GetID(){ return mID; }
