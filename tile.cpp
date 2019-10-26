#include "tile.h"

int Tile::tileWidth = -1;
int Tile::tileHeight = -1;

/**
 * @brief Tile::Tile Constructs the tile object.
 * @param windowX X co-ordinate (in pixels) of the top left corner for rendering.
 * @param windowY Y co-ordinate (in pixels) of the top left corner for rendering.
 * @param frames Vector of {row, col} co-ordinates for images in the animation.
 * @param t The type of tile.
 * @param spriteWidth The width of the animation in tiles (usually 1).
 * @param spriteHeight The height of the animation in tiles (usually 1).
 */
Tile::Tile(int windowX, int windowY, std::vector<std::pair<int, int> > frames, TileType t, int spriteWidth, int spriteHeight)
{
	x= windowX;
	y=windowY;
	myFrames=frames;
	myType=t;
	w=spriteWidth;
	h=spriteHeight;
	
}
/**
 * @brief Tile::render Uses the texture object to render a frame from the current tile.
 * @param t The Texture object to use.
 * @param frame The frame % numFrames that should be rendered.
 */
void Tile::render(Texture *t, int frame, int scale)
{
	t->render(x,y,myFrames[frame%myFrames.size()].first,myFrames[frame%myFrames.size()].second,w,h,scale);
}
