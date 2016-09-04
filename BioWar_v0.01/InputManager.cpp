#include "InputManager.h"


InputManager * InputManager::m_instance = NULL;

InputManager * InputManager::GetInstance()
{
   if( m_instance == NULL )
   {
      m_instance = new InputManager();
   }

   return m_instance;
}

void InputManager::Update()
{
   SDL_Event event;
   m_keyboard = SDL_GetKeyState( NULL );
   m_mouse = SDL_GetMouseState( NULL, NULL );
   ///SDL_JoystickUpdate();
   m_keyMap.erase( m_keyMap.begin(), m_keyMap.end() );
   m_mouseButtonMap.erase( m_mouseButtonMap.begin(), m_mouseButtonMap.end() );

   while( SDL_PollEvent( &event ) )
   {
      switch( event.type )
      {
      case SDL_KEYDOWN:         m_keyMap[ event.key.keysym.sym ] = Down; break;
      case SDL_KEYUP:           m_keyMap[ event.key.keysym.sym ] = Up;   break;
      case SDL_MOUSEMOTION:     m_mouseX =  event.motion.x; m_mouseY = event.motion.y; break;
      case SDL_MOUSEBUTTONDOWN: m_mouseButtonMap[ event.button.button ] = Down; break;
      case SDL_MOUSEBUTTONUP:   m_mouseButtonMap[ event.button.button ] = Up; break;
      case SDL_JOYBUTTONDOWN:   m_joystickButtonMap[ event.jbutton.button ] = Down; break;
      case SDL_JOYBUTTONUP:     m_joystickButtonMap[ event.jbutton.button ] = Up; break;
      case SDL_JOYHATMOTION:    m_joystickHatMap[ event.jhat.value ] = Down; break;
      case SDL_QUIT:            m_quitGame  = true; break;
      default: break;
      }
   }
}

void InputManager::SetCamera( long cameraX, long cameraY )
{
   m_cameraX = cameraX;
   m_cameraY = cameraY;
}
bool InputManager::IsMouseInside( SDL_Rect * rect )
{
   SDL_GetMouseState( &m_mouseX, &m_mouseY );
   return ( ( rect->x  < m_mouseX + m_cameraX ) &&
      ( rect->x + rect->w > m_mouseX + m_cameraX ) &&
      ( rect->y < m_mouseY + m_cameraY ) &&
      ( rect->y + rect->h > m_mouseY + m_cameraY ) );
}

int InputManager::GetMousePosX()
{
   SDL_GetMouseState( &m_mouseX, NULL );
   return m_mouseX; 
}

int InputManager::GetMousePosY()
{
   SDL_GetMouseState( NULL, &m_mouseY );
   return m_mouseY; 
}

int InputManager::GetMousePos( int &x, int &y )
{
   SDL_GetMouseState( &x, &y );
   return 0;
}

bool InputManager::IsKeyDown( int key )
{ 
   static bool pressed = false;
   return ( m_keyMap[ key ] == Down );
}

bool InputManager::IsKeyUp( int key )
{
   return ( m_keyMap[ key ] == Up );
}

bool InputManager::IsKeyPressed( int key )
{
   SDL_PumpEvents();
   m_keyboard = SDL_GetKeyState( NULL );
   return m_keyboard[key];
}

bool InputManager::IsJoystickHatPressed( int button )
{
   SDL_PumpEvents();
   int buttonPattern = SDL_JoystickGetHat( SDLBase::GetJoystick(), 0 );
   return( SDL_JoystickGetHat( SDLBase::GetJoystick(), 0 ) & button );
}

bool InputManager::IsJoystickButtonDown( int button )
{

   return ( m_joystickButtonMap[ button ] == Down );
}

bool InputManager::IsJoystickButtonUp( int button )
{
   return ( m_joystickButtonMap[ button ] == Up );
}

bool InputManager::IsJoystickButtonPressed( int button )
{
   SDL_PumpEvents();
   return ( SDL_JoystickGetButton( SDLBase::GetJoystick(), button ) == 1 );
}

bool InputManager::IsMouseDown( int button )
{
   return( m_mouseButtonMap[ button ] == Down );
}

bool InputManager::IsMouseUp( int button )
{
   return ( m_mouseButtonMap[ button ] == Up );
}

bool InputManager::IsMousePressed( int button )
{
   SDL_PumpEvents();
   m_mouse = SDL_GetMouseState( &m_mouseX, &m_mouseY );
   return ( m_mouse & button );
}

void InputManager::SetQuitGame()
{
   m_quitGame = true;
}

InputManager::InputManager() :
   m_quitGame( false )
{
}


InputManager::~InputManager(void)
{
}
