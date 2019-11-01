#include"map.h"
#include<iostream>
int Map::mapWidth = -1;
int Map::mapHeight = -1;

Map::Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight)
{
	
	std::vector<std::vector<Tile>> myMap(map.size(),std::vector<Tile>(map[0].size(),Tile(0,0,{{0,0}},Player)));
	for(int i = 0; i< map.size();i++)
	{
		for(int j = 0; j< map[i].size();j++)
		{
			myMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{map[i][j]/23,map[i][j]%23}}, Player, 1, 1, 1, 1);
		}
	
	}

	this->map = myMap;
	this->x = x;
	this->y = y;
	width = myMap.size();
	height = myMap[0].size();
	mapWidth = width * tileWidth;
	mapHeight = height * tileHeight;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	//Map(myMap, x, y, tileWidth, tileHeight);
	
}




void Map::update(Character player)
{
	this -> x = player.relativeX - WIDTH/2 + player.tileWidth/2;
	this -> y = player.relativeY - HEIGHT/2 + player.tileHeight/2; 
	bound();
	
	
}


void Map::render(Texture *t, int frame, int index, int scale)
{
	
	int relativeX = x / (tileWidth);  
	int relativeY = y / (tileHeight);

	for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
	{
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
		{
			map[i][j].x = (i * tileWidth-x); 
			map[i][j].y = (j * tileHeight-y); 
		}
	
	}	

	for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
			map[i][j].render(t, frame, index, scale);
}


void Map::bound()
{
	if(x >= width * tileWidth - WIDTH) 
		x = width * tileWidth - WIDTH;
	else if(x <= 0)
		x=0;
	if(y >= height*tileHeight - HEIGHT)
		y=height*tileHeight - HEIGHT;
	else if(y<=0)
		y=0;
}


