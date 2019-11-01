#ifndef CHARACTER_H
#define CHARACTER_H

#include "tile.h"
#include <cstdlib>


class Character : public Tile
{
	public:
		
		Character(int windowX, int windowY,
        std::vector<std::vector<std::pair<int,int>>> frames,
        TileType t, int relativeX, int relativeY,
        int spriteWidth = 1, int spriteHeight = 1, int scale = 1, int animationSpeed = 1);
		
		void setCanMove(bool b);
		void handle_event(SDL_Event &e, int val);
		void move(Direction dir, int speed);
		bool canMove(Direction dir);
		bool isCentral(Direction dir);
		
		int relativeX, relativeY;
		
		void render(Texture *t, int frame, int index, int scale = 1);
		int frameNo;
	private:
		
		void bound();
		std::vector<std::pair<int,int>> up;
		std::vector<std::pair<int,int>> down;
		std::vector<std::pair<int,int>> left;
		std::vector<std::pair<int,int>> right;
		std::vector<std::pair<int,int>> idle;
		int idleTimer;
		Direction dir;
		bool isMoving;
		void centralize(int speed);
		
};
#endif
