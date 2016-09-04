#pragma once
#include "SDLBase.h"
#include <map>

#define N_KEYS 5
#define N_MOUSE_BUTTONS 5

class InputManager
{
public:
   static InputManager * GetInstance();

   enum InputState
   {
      Down    = 1,
      Up      = 0,
   };

   void Update();

   bool IsKeyDown( int key );
   bool IsKeyUp( int key );
   bool IsKeyPressed( int key );

   bool IsJoystickButtonDown( int button );
   bool IsJoystickButtonUp( int button );
   bool IsJoystickButtonPressed( int button );
   bool IsJoystickHatPressed( int hat );

   bool IsMouseDown( int button );
   bool IsMouseUp( int button );
   bool IsMousePressed( int button );

   int GetMousePosX();
   int GetMousePosY();
   int GetMousePos( int &x, int &y );

   void SetCamera( long cameraX, long cameraY );

   bool IsMouseInside( SDL_Rect * rect );
   
   inline bool QuitGame(){ return m_quitGame; };
   void SetQuitGame();

private:
   static InputManager * m_instance;
   
   Uint8   m_mouse;
   Uint8 * m_keyboard;
   SDL_Joystick * m_joystick;
   std::map< Uint8, Uint8 > m_keyMap;
   std::map< Uint8, Uint8 > m_mouseButtonMap;
   std::map< Uint8, Uint8 > m_joystickButtonMap;
   std::map< Uint8, Uint8 > m_joystickHatMap;
   bool    m_quitGame;
   int     m_mouseX;
   int     m_mouseY;

   int     m_cameraX;
   int     m_cameraY;

   InputManager();
   ~InputManager();
};

