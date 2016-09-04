#include "GameOverState.h"
#include <sstream>
#include "InputManager.h"
#include "MenuState.h"


GameOverState GameOverState::m_instance;
GameOverState * GameOverState::GetInstance()
{
   return &m_instance;
}

GameOverState::GameOverState() :
   musicFadeIn( 300 ),
   musicFadeOut( 300 ),
   textSize( 8 )
{
}

void GameOverState::Pause()
{
   std::cout << "Game Pause" << std::endl;
}

void GameOverState::Resume()
{
   std::cout << "Game Resume" << std::endl;
}


void GameOverState::HandleEvents( GameManager * manager )
{

   InputManager::GetInstance()->Update();
   if( InputManager::GetInstance()->QuitGame() ||
      InputManager::GetInstance()->IsKeyDown( SDLK_ESCAPE ) )
      m_quit = true;
   if( InputManager::GetInstance()->IsKeyDown( SDLK_SPACE ) ||
      InputManager::GetInstance()->IsJoystickButtonDown( 9 ) )
      manager->ChangeState( MenuState::GetInstance() );
   if( m_quit )
      manager->QuitGame();
}

void GameOverState::Update( GameManager * manager )
{
}

void GameOverState::GainFocus( GameManager * manager )
{
   m_bg->Render( 0, 0 );
   //m_image->Render( m_bg->GetWidth()/2 - m_image->GetWidth()/2, m_bg->GetHeight()/2 - m_image->GetHeight()/2);
   m_text->Render( 0, 0 );

   SDLBase::RefreshScreen();
}

void GameOverState::Init()
{
   m_quit = false;
   
   m_bg        = new Sprite( "img/gameOverBg.png" );
   m_image     = new Sprite( "img/loseO.png" );
   m_music     = new Music( "sfx/stateLose.mp3", musicFadeIn, musicFadeOut );
   m_text      = new Text( "fonts/Vdj.ttf", "Pressione 'Espaco' para retornar ao jogo", 0xff, 0xff, 0xff, textSize );

   m_music->Play( 60 );
   m_text->SetPos( m_bg->GetWidth()/2 - m_text->GetBox().w/2, m_bg->GetHeight() - ( m_text->GetBox().h + 10 ) );
}

void GameOverState::CleanUp()
{
   delete m_text;
   delete m_music;
   delete m_image;
   delete m_bg;  

}


GameOverState::~GameOverState()
{
 
}
