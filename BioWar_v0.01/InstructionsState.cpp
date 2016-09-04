#include "InstructionsState.h"
#include "GameOverState.h"
#include <sstream>
#include "InputManager.h"
#include "MenuState.h"
#include "XMLLoader.h"


InstructionsState InstructionsState::m_instance;
InstructionsState * InstructionsState::GetInstance()
{
   return &m_instance;
}

InstructionsState::InstructionsState() :
   musicFadeIn( 300 ),
   musicFadeOut( 300 ),
   textSize( 8 )
{
}

void InstructionsState::Pause()
{
   std::cout << "Game Pause" << std::endl;
}

void InstructionsState::Resume()
{
   std::cout << "Game Resume" << std::endl;
}


void InstructionsState::HandleEvents( GameManager * manager )
{

   InputManager::GetInstance()->Update();
   if( InputManager::GetInstance()->QuitGame()  )
      m_quit = true;
   if( InputManager::GetInstance()->IsKeyDown( SDLK_SPACE ) ||
      InputManager::GetInstance()->IsJoystickButtonDown( 9 ) ||
      InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) )
      manager->ChangeState( MenuState::GetInstance() );
   if( m_quit )
      manager->QuitGame();
}

void InstructionsState::Update( GameManager * manager )
{
}

void InstructionsState::GainFocus( GameManager * manager )
{
   m_bg->Render( 0, 0 );

   SDLBase::RefreshScreen();
}

void InstructionsState::Init()
{
   m_quit = false;
   
   m_bg        = new Sprite( "img/intructionsScreen.png" );
   m_music     = new Music( "sfx/History1.ogg", musicFadeIn, musicFadeOut );

   XMLLoader::GetInstance()->LoadFile( "StageOne.xml" );

   m_music->Play( 60 );
}

void InstructionsState::CleanUp()
{
   delete m_music;
   delete m_bg;  
}


InstructionsState::~InstructionsState()
{
 
}