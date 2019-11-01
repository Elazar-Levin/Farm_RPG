#include"map.h"
#include<iostream>
int Map::mapWidth = -1;
int Map::mapHeight = -1;

Map::Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight, int sheetWidth)
{
	
	std::vector<std::vector<Tile>> myMap(map.size(),std::vector<Tile>(map[0].size(),Tile(0,0,{{0,0}},Player)));
	for(int i = 0; i< map.size();i++)
	{
		for(int j = 0; j< map[i].size();j++)
		{
			myMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{map[i][j]/sheetWidth,map[i][j]%sheetWidth}}, Player, 1, 1, 1, 1);
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
	//reworked these functions, as it was transposed, still not toatally sure it works properly
	for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
	{
		for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
		{
			map[j][i].x = (i * tileWidth-x); 
			map[j][i].y = (j * tileHeight-y); 
		}
	
	}	
	
	for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
		for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
			map[j][i].render(t, frame, index, scale);
	
	
	
}


void Map::bound()
{
	if(x >= width * tileWidth - WIDTH) 
		x = width * tileWidth - WIDTH;
	else if(x <= 0)
		x=0;
	if(y >= height*tileHeight - HEIGHT)
		y = height*tileHeight - HEIGHT;
	else if(y<=0)
		y=0;
}


