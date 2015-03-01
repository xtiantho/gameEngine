#ifndef __GameEngine__CoreEngine__
#define __GameEngine__CoreEngine__

#include <stdio.h>
#include "Display.h"
#include "Input.h"
#include "Game.h"

class CoreEngine
{
public:
    CoreEngine(double frameRate, Display* display, Game* game);
    ~CoreEngine();
    
    void start();
    void stop();
    void run();
    void render();
    
protected:
private:
    Display*    m_display;
    bool        m_isRunning;
    double      MILLISECONDS_PER_UPDATE;
    Game*       m_game;
    
    void initGraphics() const;
};

#endif
