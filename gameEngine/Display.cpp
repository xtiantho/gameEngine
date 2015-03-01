

#include "Display.h"
Display::Display(const int& width, const int& height, const std::string& title)
{
    std::cout << "Display Constructor!" << std::endl;
    
    /* Initialize SDL Window */
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // 2^8
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // 2^8
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // 2^8
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 2^8
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // How much data SDL will allocate for a single pixel
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // allocate space for another buffer
    
   // SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
  //  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   // SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
    
    /* Create the Window. */
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
    m_glContext = SDL_GL_CreateContext(m_window);
    
    /* look for all supported opengl functions */
    //GLenum status = glewInit();
    
    SDL_GL_SetSwapInterval(1);
    
  //  if (status != GLEW_OK)
    {
  //      std::cerr << "We failed to initialize glew." << std::endl;
    }
    
    m_isClosed = false;
}

Display::~Display()
{
    std::cout << "Destructor" << std::endl;
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Display::isClosed()
{
    return m_isClosed;
}

void Display::swapBuffers()
{
    SDL_GL_SwapWindow(m_window); //swap buffers
}

/* Have window display one buffer => Window never displays something that is in progress of being drawn.
 *  Have opengl draw on one buffer. Then they can swap and do their jobs and be more efficiently.
 */
void Display::update()
{
   // SDL_GL_SwapWindow(m_window); //swap buffers
    
    for (int i = 0; i < Input::NUM_MOUSEBUTTONS; i++)
    {
        m_input.setMouseDown(i, false);
        m_input.setMouseUp(i, false);
    }
    
    for (int i = 0; i < Input::NUM_KEYS; i++)
    {
        m_input.setKeyDown(i, false);
        m_input.setKeyUp(i, false);
    }
    
    SDL_Event e;
    
    //the input handler
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            m_isClosed = true;
        
        if (e.type == SDL_KEYDOWN)
        {
            //std::cout << "key pressed down!" << std::endl;
            int val = e.key.keysym.scancode;
            
            m_input.setKey(val, true);
            m_input.setKeyDown(val, true);
            
        }
        if (e.type == SDL_KEYUP)
        {
            // std::cout << "key up!" << std::endl;
            int val = e.key.keysym.scancode;
            
            m_input.setKey(val, false);
            m_input.setKeyUp(val, true);
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int val = e.key.keysym.scancode;
            
            m_input.setMouse(val, true);
            m_input.setMouseDown(val, true);
        }
        if (e.type == SDL_MOUSEBUTTONUP)
        {
            int val = e.key.keysym.scancode;
            
            m_input.setMouse(val, false);
            m_input.setMouseUp(val, true);
        }
    }
}
