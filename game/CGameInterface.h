//
//  gameinterface.h
//  Purpose: This is where the game is controlled. Everything starts and ends
//  here for the game.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

//------------------------------------------------------------
//------------------------------------------------------------
class CGameInterface
{
public:
    void        Init(void);
    void        Shutdown(void);
    
    void        GameFrame(void);
    
    void        KeyPressed(char character);
    void        KeyReleased(char character);
    
    bool        GetKeyState(char character) const;
    
    void        MousePressed(bool right);
    void        MouseReleased(bool right);
    
    void        MouseMoved(float deltaX, float deltaY);
    
private:
    bool        m_keys[255];
    
    float       m_MouseXDelta;
    float       m_MouseYDelta;
};

#endif // GAME_INTERFACE_H
