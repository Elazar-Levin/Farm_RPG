#include"map.h"
#include<iostream>

Map::Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight)
{
	
	std::vector<std::vector<Tile>> myMap(map.size(),std::vector<Tile>(map[0].size(),Tile(0,0,{{0,0}},Player)));
	for(int i = 0; i< map.size();i++)
	{
		for(int j = 0; j< map[i].size();j++)
		{
			myMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{map[i][j]/23,map[i][j]%23}}, Player, 1, 1, 1);
		}
	
	}

	this->map = myMap;
	this->x = x;
	this->y = y;
	width = myMap.size();
	height = myMap[0].size();
	this->tileWidth=tileWidth;
	this->tileHeight = tileHeight;
	//Map(myMap, x, y, tileWidth, tileHeight);
	
}


Map::Map(std::vector< std::vector <Tile> > map, int x, int y, int tileWidth, int tileHeight)
{
	this->map = map;
	this->x = x;
	this->y = y;
	width = map.size();
	height = map[0].size();
	//std::cout<<this->map.size();//<<" "<<map[0].size()<<std::endl;
}


void Map::render(Texture *t, int frame, int index, int scale)
{
	
	int relativeX = x / (tileWidth);  
	int relativeY = y / (tileHeight);
	//std::cout<<relativeX<<" "<<relativeY<<std::endl;
	//if(relativeX<=0)
	//	relativeX=0;
	//if(relativeY<=0)
	//	relativeY=0;
	
	for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
	{
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
		{
			map[i][j].x = (i * tileWidth-x); 
			map[i][j].y = (j * tileHeight-y); 
		}
	
	}	
	//	std::cout<<relativeX<<" "<<(t->myWin.getWidth())/ tileWidth<<" "<<width<<"\n";
	//		std::cout<<relativeY<<" "<<(t->myWin.getHeight())/ tileHeight<<" "<<height<<"\n";
	for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
	{
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
		{
			//map[i][j].x=map[i][j].x+x%t->tileWidth(index);
			//map[i][j].y=map[i][j].y+y%t->tileHeight(index);
			map[i][j].render(t, frame, index, scale);
		}
	}
}

bool Map::handle_event(SDL_Event &e, int val)
{
	if(e.type!=SDL_KEYDOWN)
		return true;
	switch(e.key.keysym.sym)
	{
		case SDLK_a: 
		case SDLK_LEFT:
			return move(Left, val);
		case SDLK_s:
		case SDLK_DOWN:
			return move(Down, val);
		case SDLK_d: 
		case SDLK_RIGHT:
			return move(Right, val);
		case SDLK_w:
		case SDLK_UP:
			return move(Up, val);
			
	}
	

}

bool Map::move(Direction dir, int speed)
{
	
	switch(dir)
	{
		case Up:
			return move(0, -speed);
		case Down:
			return move(0, speed);
		case Left:
			return move(-speed, 0);
		case Right:
			return move(speed, 0);
	}

}

bool Map::move(int x,int y)
{
	
	this->x+=x;
	this->y+=y;
	return bound();

}

bool Map::bound()
{
	bool changed = false;
	if(x >= width * tileWidth - WIDTH) 
	{	
		x = width * tileWidth - WIDTH;
		changed=true;
	}
	else if(x <= 0)
	{
		x=0;
		changed=true;
	}
	if(y >= height*tileHeight - HEIGHT)
	{
		y=height*tileHeight - HEIGHT;
		changed=true;
	}
	else if(y<=0)
	{
		y=0;
		changed=true;
	}	
	return changed;
}

bool Map::canMove(Direction dir)
{
	switch(dir)
	{
		case Up:
			if(y<=0)
				return false;
			return true;
		case Down:
			if(y >= height*tileHeight - HEIGHT)
				return false;
			return true;
		case Left:
			if(x < 0)
				return false;
			return true;		
		case Right:
			if(x >= width * tileWidth - WIDTH)
				return false;
			return true;
	}	
	return true;
}
