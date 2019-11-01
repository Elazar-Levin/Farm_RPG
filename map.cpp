#include"map.h"
#include<iostream>

int Map::mapWidth = -1;
int Map::mapHeight = -1;

Map::Map(int x, int y, int tileWidth, int tileHeight)
{
	this->x = x;
	this->y = y;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
		
}


void Map::loadFile(std::string filename, int sheetWidth)
{
	std::vector< std::vector <int > > myMap;
	std::string line;
	std::ifstream myfile;
	myfile.open (filename);
	
	if (myfile.is_open()) //process the csv to make the map
  	{
    	while ( std::getline (myfile,line) )
    	{
    		std::vector<int> row;
    		std::stringstream ss(line);
    		std::string token;
    		while (std::getline(ss, token, ',')) {
        		row.push_back(stoi(token));
    		}
      		myMap.push_back(row);
   		}
 	   	myfile.close();
  	}
	
	width = myMap.size(); //set variables after the first? load
	height = myMap[0].size();
	mapWidth = width * tileWidth;
	mapHeight = height * tileHeight;
	
	
	std::vector<std::vector<Tile>> tileMap(myMap.size(),std::vector<Tile>(myMap[0].size(),Tile(0,0,{{0,0}},Player)));
	for(int i = 0; i< myMap.size();i++)
	{
		for(int j = 0; j< myMap[i].size();j++)
		{
			tileMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{myMap[i][j]/sheetWidth,myMap[i][j]%sheetWidth}}, Player, 1, 1, 1, 1);
		}
	
	}
	map.push_back(tileMap);


}

void Map::update(Character player)
{
	this -> x = player.relativeX - WIDTH/2 + player.tileWidth/2;
	this -> y = player.relativeY - HEIGHT/2 + player.tileHeight/2; 
	bound();
	
	
}


void Map::render(Texture *t, int frame, int index, int scale)
{
	
	//going crazy and rendering many layers at once
	int relativeX = x / (tileWidth);  
	int relativeY = y / (tileHeight);
	for(int k = 0; k < map.size(); k++)
	{
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
		{
			for(int i = relativeX; i< (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
			{
				
					map[k][j][i].x = (i * tileWidth-x); 
					map[k][j][i].y = (j * tileHeight-y); 
			}
		}
	}	
	for(int k = 0; k < map.size(); k++)
		for(int j = relativeY; j < (t->myWin.getHeight())/ tileHeight + relativeY+1 && j < height; j++)
			for(int i = relativeX; i < (t->myWin.getWidth())/ tileWidth + relativeX+1 && i < width; i++)
				map[k][j][i].render(t, frame, index, scale);
	
	
	/*
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
	*/
	
	
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


