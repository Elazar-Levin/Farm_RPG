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
#include <set>

#include "window.h"
#include "texture.h"
#include "tile.h"
#include "map.h"
#include "character.h"


#define SPEED 10 
using namespace std;

int main()
{
   
    string charFilename = "Assets/character.png";
    string backgroundFileName="Assets/allImages.png";
    
    vector<Tile> objects;
    Texture myTexture;
    myTexture.loadFile(charFilename, 16, 32);
	myTexture.loadFile(backgroundFileName, 32, 32);

	std::vector< std::vector <int > > myMap;
	string line;
	ifstream myfile;
	myfile.open ("Test.csv");
	
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
  	
  	set<SDL_Keycode> movingKeys = {SDLK_w, SDLK_a, SDLK_s, SDLK_d, SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN};
  	
  	Map map(myMap,300,300, 32, 32);
  	
    bool quit = false;
	Character player(320-32,240-64, {{{2,0}, {2,1}, {2,2}, {2,3}},{{0,0},{0,1},{0,2},{0,3}},{{3,0},{3,1},{3,2},{3,3}},{{1,0},{1,1},{1,2},{1,3}}},Player, 100, 100,1,1,1,2);

    int frame=0;
 
    while(!quit){
    	SDL_Event e;
    	while(SDL_PollEvent(&e))
    	{
    		if(e.type == SDL_QUIT)
    		{
    			quit = true;
    		}
    		//TODO: Move this bulky, hideous mess, and possibly the whole event loop to another function, preferably class
    		if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
    		{
    			if(find(movingKeys.begin(), movingKeys.end(), e.key.keysym.sym) != movingKeys.end())//if this is a moving key
    			{
    				player.handle_event(e, SPEED);
    			
    			}
    		}
    		
    	}
    		
    
    	SDL_SetRenderDrawColor(myTexture.myWin.sdlRenderer, 0, 0, 0, 255);
    	SDL_RenderClear(myTexture.myWin.sdlRenderer);

    	map.update(player);
    	map.render(&myTexture, frame, 1, 1);
    
   	 	player.render(&myTexture, frame, 0, 2);
   	 	SDL_RenderPresent(myTexture.myWin.sdlRenderer);
      
        this_thread::sleep_for(chrono::milliseconds(100));
        frame++;
    }

    return 0;
}

void handle_keys(Map map, Tile player)
{

}
