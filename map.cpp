#include"map.h"

Map::Map(std::vector< std::vector <Tile> > map, int x, int y, int tileWidth, int tileHeight)
{
	this->map = map;
	this->x = x;
	this->y = y;
	width = map.size();
	height = map[0].size();

}

Map::Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight)
{
	std::vector<std::vector<Tile>> myMap(map.size(),std::vector<Tile>(map[0].size(),Tile(0,0,{{0,0}},Player)));
	

	for(int i = 0; i< map.size();i++)
	{
		for(int j = 0; j< map[i].size();j++)
		{
			myMap[i][j] = Tile(i * tileWidth,j*tileHeight, {{map[i][j]/tileWidth,map[i][j]%tileHeight}}, Player, 1, 1);
		}
	
	}
	Map(myMap, x, y, tileWidth, tileHeight);

}

void Map::render(Texture *t, int frame, int scale)
{
	int relativeX = (x / t->tileWidth());  
	int relativeY = (y / t->tileHeight());
	for(int i = relativeX; i< (t->myWin.getWidth())/ t->tileWidth() + 1 && i < width; i++)
	{
		for(int j = relativeY; j < (t->myWin.getHeight())/ t->tileHeight() + 1 && j < height; j++)
		{
			map[i][j].render(t,frame,scale);
		}
	}
}
