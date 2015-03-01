#include <iostream>
#include "CoreEngine.h"
#include <unistd.h>

using namespace std;

int main()
{
    //screen 800 width, 600 height
    Display display(800, 600, "3D Game Engine");
    
    //the game implementation inside this object
    Game game;
    
    //send the display and game references
    //60 frames per second
    CoreEngine engine(60.0f, &display, &game);
    
    //start the engine!
    engine.start();
    
    return 0;
}