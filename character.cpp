#include "character.h"
#include <iostream>
#include "map.h"

Character::Character(int windowX, int windowY,
         std::vector<std::vector<std::pair<int,int>>> frames,
         TileType t, int relativeX, int relativeY,
         int spriteWidth, int spriteHeight, int scale, int animationSpeed) : Tile(windowX, windowY, frames[1], t, spriteWidth, spriteHeight, scale, animationSpeed)
{
	this -> relativeX = relativeX;
	this -> relativeY = relativeY;
	idleTimer = 0;
	up = frames[0];
	down = frames[1];
	left = frames[2];
	right = frames[3];
	idle = frames[4];
}



void Character::bound()
{
	if(x + tileWidth >= WIDTH) 
		x = WIDTH - tileWidth;
	else if(x<=0)
		x=0;
	if(y + tileHeight >= HEIGHT)
		y = HEIGHT - tileHeight;
	else if(y<=0)
		y=0;
	if(relativeX < 0)
		relativeX = 0;
	if(relativeY < 0)
		relativeY = 0;
	if(relativeX + tileWidth > Map::mapWidth)
		relativeX = Map::mapWidth - tileWidth;
	if(relativeY + tileHeight > Map::mapHeight)
		relativeY = Map::mapHeight - tileHeight;
	
}





void Character:: render(Texture *t, int frame, int index, int scale)
{
	

	int centralX = WIDTH/2 - tileWidth/2;
	int centralY = HEIGHT/2 - tileHeight/2;
	switch(dir)
	{
		case Up:
			myFrames = up;
			break;
		case Down:
			myFrames = down;
			break;
		case Left:
			myFrames = left;
			break;
		case Right:
			myFrames = right;
			break;
	}
	//if(idleTimer >= 100)
	//{
	//	myFrames = idle;
	//	animationSpeed*=3;
	//}
	if(relativeX < centralX)
		x = relativeX;
	else if(relativeX > Map::mapWidth - centralX - tileWidth)
			x =(WIDTH - ( Map::mapWidth - relativeX) )- tileWidth;
	if(relativeY < centralY)
		y = relativeY;
	else if(relativeY > Map::mapHeight - centralY - tileHeight)
		y = HEIGHT - (Map::mapHeight - relativeY) - tileHeight;

	bound();
	if(!isMoving)//&& idleTimer<100)
		frame = 0;
//		idleTimer++;
		
	
	Tile::render(t, frame, index, scale);
}

void Character::centralize(int speed)
{
	int centralX = WIDTH/2 - tileWidth/2;
	int centralY = HEIGHT/2 - tileHeight/2;
	if(abs(centralX - x) < speed)
		x = centralX;
	if(abs(centralY - y) < speed)
		y = centralY;
}

void Character::handle_event(SDL_Event &e,int val)
{	
	//centralize(val);
	if(e.type==SDL_KEYUP)
	{
		isMoving = false;
		return;		
	}
	isMoving = true;
	//if(idleTimer>=100)
	//	animationSpeed/=3;
	//idleTimer = 0;
	switch(e.key.keysym.sym)
	{
		case SDLK_a: 
		case SDLK_LEFT:
			relativeX -= val;
			dir = Left;
			break;
		
		case SDLK_s:
		case SDLK_DOWN:
			relativeY += val;
			dir = Down;
			break;
			
			
		case SDLK_d: 
		case SDLK_RIGHT:
			relativeX += val;
			dir = Right;
			break;
			
			
		case SDLK_w:
		case SDLK_UP:
			relativeY -=val;
			dir = Up;
			break;
	}
	bound();

}

