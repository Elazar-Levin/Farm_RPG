#ifndef TILE_H
#define TILE_H

#include "texture.h"
#include <vector>

/**
 * \file tile.h Header file for Animated Sprites to render to screen.
 */

/// Enumeration representing the type of the tile. This is useful
/// later when we code the game logic.
enum TileType{Player};

enum Direction{Up, Down, Left, Right};

/**
 * @brief The Tile class representing an animated sprite to render to the screen.
 */
class Tile
{
public:
    Tile(int windowX, int windowY,
         std::vector<std::pair<int,int>> frames,
         TileType t,
         int spriteWidth = 1, int spriteHeight = 1, int scale = 1);

   
    int x, y, w, h; // w & h are measured in sprite sheet blocks
    int scale;
    std::vector<std::pair<int,int>> myFrames;

    TileType myType;

    // Static variables are shared between all instances of the class
    static int tileWidth, tileHeight; // measured in pixels

    
    virtual void render(Texture *t, int frame, int index, int scale = 1);
    
};

#endif // TILE_H
