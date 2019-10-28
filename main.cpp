#include <iostream>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "map.h"


using namespace std;

int main()
{
    // SpriteSheet Filename
    //string spriteFilename = SPRITEFILENAME; // Leave this line
    string charFilename = "Assets/character.png";
    string backgroundFileName="Assets/allImages.png";
    Texture myTexture;//, bgTexture;
    myTexture.loadFile(charFilename, 16, 32);
	myTexture.loadFile(backgroundFileName, 32, 32);

	std::vector< std::vector <int > > myMap;
	string line;
	ifstream myfile;
	myfile.open ("Test.csv");
	if (myfile.is_open())
  	{
    	while ( std::getline (myfile,line) )
    	{
    		std::vector<int> row;
    		std::stringstream ss(line);
    		std::string token;
    		while (std::getline(ss, token, ',')) {
        		row.push_back(stoi(token));
    		}
      		//cout << line << '\n';
      		myMap.push_back(row);
   		}
 	   	myfile.close();
  	}
  	
  	Map map(myMap,-100,-100, 32, 32);
  
    // Setup and Load Texture object here
    bool quit = false;
	Tile player(0,0, {{0,0}, {0,1}, {0,2}, {0,3}},Player,1,1);
    int frame=0;
   	//charTexture.scaleGraphics(30,40);
    while(!quit){
    	SDL_Event e;
    	while(SDL_PollEvent(&e))
    	{
    		if(e.type == SDL_QUIT)
    		{
    			quit = true;
    		}
    	//	charTexture.handle_event(e, 30, 40);
    		//player.handle_event(e);
    	
    	}
    	SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 255);
    	SDL_RenderClear(myTexture.myWin.sdlRenderer);
    	map.render(&myTexture, frame, 1, 1);
    	map.move(0,20);
   	 	player.render(&myTexture, frame, 0, 2);
   	 	
   	 	SDL_RenderPresent(myTexture.myWin.sdlRenderer);
      
        this_thread::sleep_for(chrono::milliseconds(100));
        frame++;
    }

    return 0;
}
