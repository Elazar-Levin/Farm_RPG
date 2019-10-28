#ifndef TEXTURE_H
#define TEXTURE_H

/**
 * \file texture.h Header file for SDL Texture Wrapper
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"

#include <string>
#include <vector>
/**
 * @brief The Texture class wraps around the SDL hardware textures.
 *
 * This class allows us to render portions of a larger sprite sheet
 * to specific co-ordinates on the screen.
 */

class Texture
{
public:    
    Texture();
    ~Texture();

    void loadFile(std::string filename, int tileWidth, int tileHeight);
    void free(int index);
    virtual void render(int x, int y, SDL_Rect src, int index, int scale=1);
    virtual void render(int x, int y, int ssRow, int ssCol, int index, int w = 1, int h = 1, int scale = 1);

    SDL_Rect getSpritePosition(int ssRow, int ssCol, int index, int width = 1, int height = 1);

    int sheetWidth(int index);
    int sheetHeight(int index);
    int tileWidth(int index);
    int tileHeight(int index);

    void handle_event(SDL_Event &e, int rows, int cols);
    void scaleGraphics(int rows, int cols);

    Window myWin;
    
protected:
    //SDL_Texture *myTexture; ///< Pointer to the SDL Hardware Texture
   	
   	std::vector< SDL_Texture* > myTextures; // List of pointers to the SDL Hardware Textures
   	
   	std::vector< int > myWidths; //List of widths of each Sprite sheet
   	std::vector< int > myHeights;//List of heights of each Sprite sheet
    //int myWidth, myHeight;  ///< Width & Height of the Sprite Sheet
    
    std::vector< int > myTileWidths;
    std::vector< int > myTileHeights;
    //int myTileWidth, myTileHeight; ///< Width & Height of each tile

};

#endif // TEXTURE_H
