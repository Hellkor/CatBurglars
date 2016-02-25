#include "Grid.h"
#include "GameObject.h"
#include "Crate.h"


Grid::Grid(){

}
bool Grid::canCrateMove(gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities){

	TileLayer mTiles = *Tiles;
	std::vector<Entity*> mEntities = *Entities;
	for each (Entity *e in mEntities){
		
		if (GameObject *object = dynamic_cast<GameObject*>(e)){

			if (object->GetPosition() == sf::Vector2i(position.x * 64, position.y * 64)){
				if (object->isSolid()){
					return false;
				}
				else return true;

			}


		}
		//Check if a type of cat can move the crate
		//if (Cat *cat = dynamic_cast<Cat*>(e)){
		//	if (!(cat->canPushCrate)){
		//		return false;
		//	}
			
		//}
	}

	if (position.x > -1 && position.y > -1 && position.x < mTiles[1].size() && position.y < mTiles.size()){
		if (mTiles[position.y][position.x]->GetID() > 0){
			return false;
		}
		else return true;

	}
	else return false;

	
}
bool Grid::isTilePassable(GameObject *gameobject, gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities){
	
	TileLayer mTiles = *Tiles;
	std::vector<Entity*> mEntities = *Entities;
	

	//////////////////// �NDRA S� ALLA KATTER EJ KAN PUTTA
	
	
	for each (Entity *e in mEntities){
		if (Cat *cat = dynamic_cast<Cat*>(gameobject)) {
			if (cat->canPushCrate) {
				if (Crate *crate = dynamic_cast<Crate*>(e)) {

					if ((gameobject->getCoords().x == position.x) && (gameobject->getCoords().y - 1 == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x) {
						crate->moveForward(Tiles, Entities);
					}
					if ((gameobject->getCoords().x == position.x) && (gameobject->getCoords().y + 1 == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x) {
						crate->moveBackWards(Tiles, Entities);
					}
					if ((gameobject->getCoords().x + 1 == position.x) && (gameobject->getCoords().y == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x) {
						crate->moveRight(Tiles, Entities);
					}
					if ((gameobject->getCoords().x - 1 == position.x) && (gameobject->getCoords().y == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x) {
						crate->moveLeft(Tiles, Entities);
					}

				}

			}
		}
		
		if (GameObject *object = dynamic_cast<GameObject*>(e)){

			
			
			if (object->GetPosition() == sf::Vector2i(position.x * 64, position.y * 64)){
				if (object->isSolid()){
					return false;
				}

			}
			

		}
	}
	
	
	if (position.x > -1 && position.y > -1 && position.x < mTiles[1].size() && position.y < mTiles.size()){
		if (mTiles[position.y][position.x]->GetID() > 0){
		  return false;
		}
		else return true;

	}
	else return false; 
}

bool Grid::canCatDash(gridvector originalpos, gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities) {
	TileLayer mTiles = *Tiles;
	std::vector<Entity*> mEntities = *Entities;
	for each (Entity *e in mEntities) {
		if (GameObject *object = dynamic_cast<GameObject*>(e)) {



			if (object->GetPosition() == sf::Vector2i(position.x * 64, position.y * 64)) {
				if (object->isSolid()) {
					return false;
				}

			}


		}
	}


	if (position.x > -1 && position.y > -1 && position.x < mTiles[1].size() && position.y < mTiles.size()) {
		if (mTiles[position.y][position.x]->GetID() > 0) {
			return false;
		}
		else return true;

	}
	else return false;
}

