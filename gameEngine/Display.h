

#ifndef __GameEngine__Display__
#define __GameEngine__Display__

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Input.h"
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

class Display
{
public:
    Display(const int& width, const int& height, const std::string& title);
    ~Display();
    
    void update();
    bool isClosed();
    void swapBuffers();
    inline const Input& getInput() const { return m_input; }
protected:
private:
    SDL_Window*   m_window;
    SDL_GLContext m_glContext;
    bool          m_isClosed;
    Input         m_input;
};

#endif 
