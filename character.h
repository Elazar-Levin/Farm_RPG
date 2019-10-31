#ifndef CHARACTER_H
#define CHARACTER_H

#include "tile.h"

class Character : public Tile
{
	public:
		
		Character(int windowX, int windowY,
        std::vector<std::vector<std::pair<int,int>>> frames,
        TileType t,
        int spriteWidth = 1, int spriteHeight = 1, int scale = 1);
		
		void setCanMove(bool b);
		int handle_event(SDL_Event &e, int val);
		void move(Direction dir, int speed);
		bool canMove(Direction dir);
		bool isCentral(Direction dir);
	private:
		void move(int x, int y);
		void bound();
		std::vector<std::pair<int,int>> up;
		std::vector<std::pair<int,int>> down;
		std::vector<std::pair<int,int>> left;
		std::vector<std::pair<int,int>> right;
		std::vector<std::pair<int,int>> curr;
			
		
};



#endif
