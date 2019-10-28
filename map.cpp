#include"map.h"
#include<iostream>

Map::Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight)
{
	
	std::vector<std::vector<Tile>> myMap(map.size(),std::vector<Tile>(map[0].size(),Tile(0,0,{{0,0}},Player)));
	for(int i = 0; i< map.size();i++)
	{
		for(int j = 0; j< map[i].size();j++)
		{
			myMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{map[i][j]/23,map[i][j]%23}}, Player, 1, 1);
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
	bound(t);
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

void Map::move(int x,int y)
{
	this->x+=x;
	this->y+=y;

}

void Map::bound(Texture *t)
{
	if(x>=width*tileWidth - t->myWin.getWidth())
		x=width*tileWidth - t->myWin.getWidth();
	else if(x<=0)
		x=0;
	if(y>=height*tileHeight - t->myWin.getHeight())
		y=height*tileHeight - t->myWin.getHeight();
	else if(y<=0)
		y=0;
	

}
