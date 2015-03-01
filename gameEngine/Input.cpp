#include "Input.h"
#include <iostream>

Input::Input()
{
    //set them all to false
    memset(m_inputs, 0, NUM_KEYS*sizeof(bool));
    memset(m_downKeys, 0, NUM_KEYS * sizeof(bool));
    memset(m_upKeys, 0, NUM_KEYS * sizeof(bool));
    
    memset(m_mouseInput, 0, NUM_MOUSEBUTTONS * sizeof(bool));
    memset(m_downMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
    memset(m_upMouse, 0, NUM_MOUSEBUTTONS * sizeof(bool));
}

Input::~Input()
{
    //dtor
}