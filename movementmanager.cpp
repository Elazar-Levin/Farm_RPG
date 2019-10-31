#include "movementmanager.h"

MovementManager::MovementManager(Map *map, Character *player, std::vector<Tile> *objects)
{
	this->map = map;
	this->player = player;
	this-> objects = objects;


}

void MovementManager::move(Direction dir, int speed, int &frame)
{
	
	if(player-> isCentral(dir) )
	{
		map->move(dir, speed);
		if(!map->canMove(dir))
			player->move(dir, speed);
		else
			player->move(dir, 0);
	}
	else
	{
		int midX = WIDTH/2 - player -> tileWidth/2;
		int midY = HEIGHT/2 - player -> tileHeight/2;
		switch(dir)
		{
			case Left:
				if( player -> x > midX)
				{
					if(player -> x - midX <= speed)
					{
						player -> move(dir, player -> x - midX);
					}
					else
					{
						player -> move(dir, speed);
					}
				}
				break;
			case Right:
				if( midX > player-> x)
				{
					if(midX - player -> x <= speed)
					{
						player -> move(dir, midX - player -> x);
					}
					else
					{
						player -> move(dir, speed);
					}
				}
				break;
			case Up:
				if( player -> y > midY)
				{
					if(player -> y - midY <= speed)
					{
						player -> move(dir, player -> y - midY);
					}
					else
					{
						player -> move(dir, speed);
					}
				}
				break;
			case Down:
				if( midY > player-> y)
				{
					if(midY - player -> y <= speed)
					{
						player -> move(dir, midY - player -> y);
					}
					else
					{
						player -> move(dir, speed);
					}
				}
				break;
		}
	
	}


	//map->move(dir, speed);
	
	
	//if(!map->canMove(dir))
	//	player->move(dir, speed);
	if(player->canMove(dir))
		frame = -1;
	else
		frame = 0;
		

	//TODO:do objects

	//for(int i=0; i<objects->size(); i++)
	//	objects[i]->move(dir, speed);


}

void MovementManager::handle_event(SDL_Event &e, int &frame, int val)
{
	if(e.type!=SDL_KEYDOWN)
		move(Up, 0, frame);
	switch(e.key.keysym.sym)
	{
		case SDLK_a: 
		case SDLK_LEFT:
			move(Left, val, frame);
			break;
		case SDLK_s:
		case SDLK_DOWN:
			move(Down, val, frame);
			break;
		case SDLK_d: 
		case SDLK_RIGHT:
			move(Right, val, frame);
			break;
		case SDLK_w:
		case SDLK_UP:
			move(Up, val, frame);
			break;
	}

}
