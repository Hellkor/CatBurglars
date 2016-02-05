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

			}


		}
	}

	if (position.x > -1 && position.y > -1 && position.x < mTiles[1].size() && position.y < mTiles.size()){
		if (mTiles[position.y][position.x]->GetID() > 0){
			return false;
		}
		else return true;

	}
	else return false; // TYDLIGEN SKAPAR DETTA PROBLEM

	
}
bool Grid::isTilePassable(gridvector originalpos, gridvector position, TileLayer *Tiles, std::vector<Entity*> *Entities){
	
	TileLayer mTiles = *Tiles;
	std::vector<Entity*> mEntities = *Entities;
	
	cout << originalpos.x << " " << originalpos.y << endl;
	cout << position.x << " " << position.y << endl;

	/*if (originalpos.x + 1 == position.x  && originalpos.y == position.y){
		direction = 3;
	}
	else if (originalpos.x - 1 == position.x && originalpos.y == position.y){
		direction = 4;
	}
	else if (originalpos.x == position.x  && originalpos.y + 1  == position.y){
		direction = 1;
	}
	else if (originalpos.x == position.x + 1 && originalpos.y - 1 == position.y){
		direction = 2;
	}*/
	
	

	for each (Entity *e in mEntities){

		if (Crate *crate = dynamic_cast<Crate*>(e)){

			if ((originalpos.x == position.x)  && (originalpos.y - 1 == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x ){
				crate->moveForward(Tiles, Entities);
			}
			if ((originalpos.x == position.x) && (originalpos.y + 1 == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x){
				crate->moveBackWards(Tiles, Entities);
			}
			if ((originalpos.x + 1 == position.x) && (originalpos.y == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x){
				crate->moveRight(Tiles, Entities);
			}
			if ((originalpos.x - 1 == position.x) && (originalpos.y == position.y) && position.y == crate->getCoords().y && position.x == crate->getCoords().x){
				crate->moveLeft(Tiles, Entities);
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
	else return false; // TYDLIGEN SKAPAR DETTA PROBLEM
	

	
	
	
	
	

}

