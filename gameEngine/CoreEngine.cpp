#include "CoreEngine.h"
//#include "RenderUtil.h"

#include <iostream>

CoreEngine::CoreEngine(double frameRate, Display* display, Game* game)
{
    initGraphics();
    m_isRunning = false;
    MILLISECONDS_PER_UPDATE = 1.0 / frameRate; //60 frames per second
    m_display = display;
    m_game = game;
}

CoreEngine::~CoreEngine()
{
    //dtor
}

void clearScreen() 
{
    //todo: stencil buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreEngine::start()
{
    m_isRunning = true;
    run();
}

void CoreEngine::stop()
{
    m_isRunning = false;
}

void CoreEngine::render()
{
    clearScreen();
    m_game->render();
}

void CoreEngine::run()
{
    double previousTime = (double) SDL_GetTicks() / 1000.0;
    double currentTime, elapsedTime;
    double lag = 0.0;
    int frames = 0;
    double frameCount = 0.0;
    
    //main game loop
    while(m_isRunning)
    {
        bool shouldRender = false;
        if(m_display->isClosed())
            stop();
        currentTime = (double) SDL_GetTicks() / 1000.0;
        elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        
        lag += elapsedTime;
        frameCount += elapsedTime;
        
        if(frameCount >= 1.0)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            frameCount = 0.0;
        }
        
        while(lag > MILLISECONDS_PER_UPDATE)
        {
            shouldRender = true;
            
            m_display->update();
            m_game->processInput(m_display->getInput(), (float) (MILLISECONDS_PER_UPDATE));
            m_game->update((float)MILLISECONDS_PER_UPDATE);
            
            //update game
            lag -= MILLISECONDS_PER_UPDATE;
        }
        
        if (shouldRender)
        {
            render();
            m_display->swapBuffers();
            frames++;
        }
        else
        {
            SDL_Delay(1);
        }
    }
}

void CoreEngine::initGraphics() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    //every face that is drawn in clockwise order is a frontface
    glFrontFace(GL_CW);
    glCullFace(GL_BACK); //get rid of the backface
    
    //try reversing the vertex order if something is not showing up..
    
    //opengl draws two things.. one facing away and one facing towards you
    //this will allow us to save expensive calculations that would otherwise
    //be spent on triangles that aren't even visible on the the screen
    glEnable(GL_CULL_FACE);
    
    //opengl keeps track of the z component.. it will test it
    //and will draw closer things to the screen first
    glEnable(GL_DEPTH_TEST);
    
    //TODO - Depth clamp
    glEnable(GL_DEPTH_CLAMP);
    
    glEnable(GL_TEXTURE_2D);
    
    //screen does a gamma correction
    //want to send colors with a slight exponential increase,
    //which we get with this function
    //glEnable(GL_FRAMEBUFFER_SRGB);
}
