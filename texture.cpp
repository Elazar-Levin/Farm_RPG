#include "texture.h"
#include "stdexcept"
#include <stdio.h>

using namespace std;

/**
 * @brief Texture::Texture Default constructor.
 *
 * Initialises variables to sensible defaults.
 */
Texture::Texture()
{
	
}

/**
 * @brief Texture::~Texture Destructor.
 *
 * Should free the underlying SDL texture if it exists, and delete all entries in the vector
 */
Texture::~Texture()
{
	for(int i = 0; i < myTextures.size(); i++ )
		free(i);
}

/**
 * @brief Texture::loadFile Load a sprite sheet from a PNG file.
 * @param filename Sprite sheet filename.
 * @param tileWidth The width of each tile in pixels.
 * @param tileHeight The height of each tile in pixels.
 */
void Texture::loadFile(std::string filename, int tileWidth, int tileHeight)
{
    // Make sure we don't leak memory
    //free();



    // Load the image
    SDL_Surface* loadedSurface = IMG_Load( filename.c_str() );
    // Check that it loaded successfully
    if(loadedSurface == nullptr)
        throw runtime_error(std::string("Couldn't load sprite sheet: ") + IMG_GetError());

    // Key out the background of the image (Black = 0, 0, 0)??
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );

    // Create the SDL Texture to effeciently access parts of the image
    SDL_Texture *myTexture = nullptr;

   
	myTexture = SDL_CreateTextureFromSurface(myWin.sdlRenderer, loadedSurface );
    
    //myTexture = SDL_CreateTextureFromSurface(myWin.sdlRenderer, loadedSurface );
    
    
    if(myTexture == nullptr)
        throw runtime_error(std::string("Couldn't create sprite texture: ") + SDL_GetError());
	
	
	myTextures.push_back(myTexture);
	
    // Remember width and height
    myWidths.push_back(loadedSurface->w);
    myHeights.push_back(loadedSurface->h);
    //myWidth  = loadedSurface->w;
    //myHeight = loadedSurface->h;

    // Remember the tile width and height
    
    myTileWidths.push_back(tileWidth);
    myTileHeights.push_back(tileHeight);
    //myTileWidth  = tileWidth;
    //myTileHeight = tileHeight;

    // Now that we've created the texture, we can free the surface
    SDL_FreeSurface(loadedSurface);
}

/**
 * @brief Texture::free If the SDL texture exists, then free it.
 */
void Texture::free(int index)
{
    // Check whether there is actually a texture to free
    if(myTextures[index] != nullptr){
        // Destroy the SDL texture
        SDL_DestroyTexture(myTextures[index]);
		myTextures[index]=nullptr;
		myWidths[index]=-1;
		myHeights[index]=-1;
		myTileWidths[index]=-1;
		myTileHeights[index]=-1;
		
		
	}
	myTextures.erase(myTextures.begin() + index);
	myHeights.erase(myHeights.begin() + index);
	myWidths.erase(myWidths.begin() + index);
	myTileWidths.erase(myTileWidths.begin() + index);
	myTileHeights.erase(myTileHeights.begin() + index);
}

/**
 * @brief Texture::render An area of the sprite sheet to the screen.
 * @param x Screen co-ordinate to render the sprite.
 * @param y Screen co-ordinate to render the sprite.
 * @param src Area of the sprite sheet that should be rendered.
 */
void Texture::render(int x, int y, SDL_Rect src, int index, int scale)
{
	SDL_Rect dest;
   	dest.x = x;
   	dest.y = y;
   	dest.w = src.w*scale;
   	dest.h = src.h*scale;
   	SDL_RenderCopy(myWin.sdlRenderer,myTextures[index],&src,&dest);
  
}
/**
 * @brief Texture::render Render a sprite tile to the screen.
 * @param x Screen co-ordinate to render the sprite.
 * @param y Screen co-ordinate to render the sprite.
 * @param ssRow The sprite row in the sprite sheet grid
 * @param ssCol The sprite column in the sprite sheet grid
 * @param w The width of the sprite in tiles.
 * @param h The height of the sprite in tiles.
 */
void Texture::render(int x, int y, int ssRow, int ssCol, int index, int w, int h, int scale)
{
	SDL_Rect src = getSpritePosition(ssRow, ssCol, index, w, h);
	render(x, y, src, index, scale);
}

/**
 * @brief Texture::getSpritePosition Calculate the exact co-ordinates of a sprite in the grid
 * @param ssRow Sprite Row
 * @param ssCol Sprite Column
 * @param width Width of the sprite measured in Tiles
 * @param height Height of the sprite measured in Tiles
 * @return An SDL_Rect that can be used by the render function to blit the sprit to the screen
 */
SDL_Rect Texture::getSpritePosition(int ssRow, int ssCol,int index, int width, int height)
{
	SDL_Rect pos;
	pos.x=ssCol*myTileWidths[index];
	pos.y=ssRow*myTileHeights[index];
	pos.w=width*myTileWidths[index];
	pos.h=height*myTileHeights[index];
	return pos;
}

/**
 * @brief Texture::sheetWidth
 * @return Width of the sprite sheet in pixels
 */
int Texture::sheetWidth(int index)
{
	return  myWidths[index];
}

/**
 * @brief Texture::sheetHeight
 * @return Height of the sprite sheet in pixels
 */
int Texture::sheetHeight(int index)
{
	return myHeights[index];
}

/**
 * @brief Texture::tileWidth
 * @return Width of each sprite tile in pixels
 */
int Texture::tileWidth(int index)
{
	return myTileWidths[index];
}

/**
 * @brief Texture::tileHeight
 * @return Height of each sprite tile in pixels
 */
int Texture::tileHeight(int index)
{
	return myTileHeights[index];
}

/**
 * @brief Texture::handle_event Handles Window Resize Events
 * @param e SDL_Event object.
 * @param rows Number of rows in the world.
 * @param rows Number of columns in the world.
 */
void Texture::handle_event(SDL_Event &e, int rows, int cols)
{
 /*
    if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
        scaleGraphics(rows, cols);
    }
 */
}

/**
 * @brief Texture::scaleGraphics Scales the SDL_Renderer
 * @param rows Number of rows in the world.
 * @param rows Number of columns in the world.
 */
 
void Texture::scaleGraphics(int rows, int cols)
{
 /*   int win_width, win_height;
    SDL_GetWindowSize(myWin.sdlWindow, &win_width, &win_height);

    float scaleX = win_width/(cols*double(tileWidth()));
    float scaleY = win_height/(rows*double(tileHeight()));

    SDL_RenderSetScale(myWin.sdlRenderer, scaleX, scaleY );
 */
}


