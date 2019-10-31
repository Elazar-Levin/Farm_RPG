#include "character.h"
#include <iostream>

Character::Character(int windowX, int windowY,
         std::vector<std::vector<std::pair<int,int>>> frames,
         TileType t,
         int spriteWidth, int spriteHeight, int scale) : Tile(windowX, windowY, frames[0], t, spriteWidth, spriteHeight, scale)
{
	up = frames[0];
	down = frames[1];
	left = frames[2];
	right = frames[3];
	curr = up;
	
}

void Character::move(Direction dir, int speed)
{
	//if(speed == 0)
	//	return;
	switch(dir)
	{
		case Up:
			move(0, -speed);
			myFrames = up;
			break;
		case Down:
			move(0, speed);
			myFrames = down;
			break;
		case Left:
			move(-speed, 0);
			myFrames = left;
			break;
		case Right:
			move(speed, 0);
			myFrames = right;
			break;
	}

}

void Character::move(int x, int y)
{
	this->x+=x;
	this->y+=y;
	bound();

}

void Character::bound()
{
	if(x + tileWidth >= WIDTH) 
	{	
		x = WIDTH - tileWidth;
	}
	else if(x<=0)
	{
		x=0;
	}
	if(y + tileHeight >= HEIGHT)
	{
		y = HEIGHT - tileHeight;
	}
	else if(y<=0)
	{
		y=0;
	}	
}

bool Character::canMove(Direction dir)
{
	switch(dir)
	{
		case Up:
			if(y<=0)
				return false;
			return true;
		case Down:
			if(y >= HEIGHT - tileHeight)
				return false;
			return true;
		case Left:
			if(x < 0)
				return false;
			return true;		
		case Right:
			if(x >= WIDTH - tileWidth)
				return false;
			return true;
	}	
	return true;


}

bool Character::isCentral(Direction dir)
{
	int centralX = WIDTH/2-tileWidth/2;
	int centralY = HEIGHT/2-tileHeight/2;
	switch(dir)
	{
		case Up:
		case Down:
		return y == centralY;
		
		case Left:
		case Right:
		return x == centralX;
	
	}

	return true;

}

//THIIIS FUNCTION IS BULLSHIT, NEEDS SERIOUS REVISION
int Character::handle_event(SDL_Event &e,int val)
{	
/*
	if(e.type==SDL_KEYUP)
	{
		return 0;		
	}
	switch(e.key.keysym.sym)
	{
		case SDLK_a: 
		case SDLK_LEFT:
			if(canMove && x - val >= 0)
				x-= val;
			else if(canMove && x - val < 0)
				x = 0;
			myFrames = left;
			return -1;
		case SDLK_s:
		case SDLK_DOWN:
			if(canMove && y + tileHeight + val <= t -> myWin.getHeight())
				y+=val;
			else if(canMove && y + tileHeight * 2 + val > t -> myWin.getHeight()) //TODO: hardcoded the 2 for now, change it later to work with scale
				y = t -> myWin.getHeight() - tileHeight*2;
			myFrames = down;
			return -1;
		case SDLK_d: 
		case SDLK_RIGHT:
			if(canMove && x + tileWidth*2 + val <= t -> myWin.getWidth())
				x+= val;
			else if(canMove && x + tileWidth + val > t -> myWin.getWidth())
				x = t -> myWin.getWidth() - tileWidth*2;
			myFrames = right;
			return -1;
			
		case SDLK_w:
		case SDLK_UP:
			if(canMove && y - val >= 0)
				y-= val;
			else if(canMove && y - val < 0)
				y = 0;
			myFrames = up;
			return -1;
			
	}
	*/
	return 3;
	

}

