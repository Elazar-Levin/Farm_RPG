#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tile.h"
#include "texture.h"
#include "window.h"
#include "character.h"

#include <vector>


class Map
{
	public:
		Map(std::vector< std::vector <int> > map, int x, int y, int tileWidth, int tileHeight);
		void render(Texture *t, int frame, int index, int scale = 1);
		void update(Character player);
		static int mapWidth, mapHeight;		
		
	private:
		std::vector< std::vector <Tile> > map;
		int x, y; //current position of the screen on the map
		int width, height; //width and height in tiles of the map
		int tileWidth, tileHeight;
		void bound();
};

#endif
