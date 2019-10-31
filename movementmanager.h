#ifndef MOVEMENT_MANAGER_H
#define MOVEMENT_MANAGER_H

#include "map.h"
#include "character.h"
#include "tile.h"
#include "texture.h"
#include "window.h"
#include <vector>

class MovementManager
{
	public:
		MovementManager(Map *map, Character *player, std::vector<Tile> *objects);
		void handle_event(SDL_Event &e, int &frame, int val = 0);
		

	private:
		Map *map;
		Character *player;
		std::vector<Tile> *objects;
		
		void move(Direction dir, int speed, int &frame);




};





#endif
