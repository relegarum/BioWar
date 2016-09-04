#include "MenuState.h"
#include "IntroState.h"
#include "StageOneState.h"
#include "InstructionsState.h"
#include "InputManager.h"

MenuState MenuState::m_instance;
MenuState * MenuState::GetInstance()
{
   return &m_instance;
}


void MenuState::Init()
{
   std::string lazyFontString("fonts/Vdj.ttf");
   m_background = new Sprite( "img/menuNewBG.png" );
   //m_logo       = new Sprite( "img/logoBioWar.jpg" );
   
   Sprite * buttonSprite1   = new Sprite( "img/btn3.png" );
   Sprite * buttonSprite2   = new Sprite( "img/btn3.png" );
   Sprite * buttonSprite3   = new Sprite( "img/btn3.png" );
   Sprite * buttonSprite4   = new Sprite( "img/btn3.png" );
   Text   * textBt1         = new Text( "fonts/rpg__.ttf", "New Game", 0xFF, 0xFF, 0xFF, 10 );
   Text   * textBt2         = new Text( "fonts/rpg__.ttf", "Instructions", 0xFF, 0xFF, 0xFF, 10 );
   Text   * textBt3         = new Text( "fonts/rpg__.ttf", "Options", 0xFF, 0xFF, 0xFF, 10 );
   Text   * textBt4         = new Text( "fonts/rpg__.ttf", "Quit Game", 0xFF, 0xFF, 0xFF, 10 );


   float buttonXPosition = ( m_background->GetWidth()*0.5 ) - buttonSprite1->GetWidth()*0.5;
   float buttonYStartPosition = m_background->GetHeight()*0.5 + TILE_HEIGHT*0.7;
   float halfButtonHeight = buttonSprite1->GetHeight()*0.5;
   double buttonHeight = buttonSprite1->GetHeight();
   double buttonWidth = buttonSprite1->GetWidth();

   Button * newGameItem  = new Button( buttonSprite1, IntroState::GetInstance(), buttonXPosition, buttonYStartPosition + 1*( halfButtonHeight ),
      buttonWidth,
      buttonHeight, 
      textBt1 );

   Button * continueItem = new Button( buttonSprite2, InstructionsState::GetInstance(), buttonXPosition, buttonYStartPosition + 2*( halfButtonHeight ),
      buttonWidth,
      buttonHeight, 
      textBt2 );
   Button * optionsItem  = new Button( buttonSprite3, NULL, buttonXPosition, buttonYStartPosition + 3*( halfButtonHeight ),
      buttonWidth,
      buttonHeight, 
      textBt3 );

   Button * quitItem     = new Button( buttonSprite4, NULL, buttonXPosition, buttonYStartPosition + 3*( halfButtonHeight ),
      buttonWidth,
      buttonHeight, 
      textBt4 );

   m_buttonList.push_back( newGameItem );
   m_buttonList.push_back( continueItem );
   /*m_buttonList.push_back( optionsItem );*/
   m_buttonList.push_back( quitItem );

   m_music = new Music( "sfx/mainTitleloop.ogg", 3000, 3000 );
   m_music->Play( -1 );
}

void MenuState::CleanUp()
{
   delete m_music;
   while( !m_buttonList.empty() )
   {
      Button * btn = m_buttonList.back();
      m_buttonList.pop_back();
       
      delete btn->GetSprite();
      delete btn;
   }
   delete m_background;
   //delete m_logo;
}

void MenuState::Pause()
{
   std::cout << "Menu Pause" << std::endl;
}

void MenuState::Resume()
{
   std::cout << "Menu Resume" << std::endl;
}

void MenuState::GainFocus( GameManager *manager )
{
   m_background->Render( 0 ,0 );
   //m_logo->Render( m_background->GetWidth()*0.5 - m_logo->GetWidth()*0.5, m_background->GetHeight()*0.1 ); 
   for( std::list< Button* >::iterator itr = m_buttonList.begin();
      itr != m_buttonList.end();
      ++itr )
   {
      (*itr)->Render();
   }
}

void MenuState::HandleEvents( GameManager *manager )
{
   InputManager::GetInstance()->Update();

   //ClickButton And Change State
   for( std::list< Button* >::reverse_iterator itr = m_buttonList.rbegin();
      itr != m_buttonList.rend();
      ++itr )
   {
      (*itr)->InputHandle();
   }

   if( ( InputManager::GetInstance()->IsKeyPressed( SDLK_1 ) &&
      InputManager::GetInstance()->IsKeyPressed( SDLK_2 ) &&
      InputManager::GetInstance()->IsKeyPressed( SDLK_3 ) ) ||
      ( InputManager::GetInstance()->IsJoystickButtonDown( 4 ) &&
        InputManager::GetInstance()->IsJoystickButtonDown( 5 ) &&
        InputManager::GetInstance()->IsJoystickButtonDown( 6 ) ) )
   {
      SDLBase::FullScreen();
   }

   if( InputManager::GetInstance()->IsJoystickButtonDown( 9 ) ||
      InputManager::GetInstance()->IsKeyPressed( SDLK_RETURN ) )
   {
      manager->ChangeState( IntroState::GetInstance() );
   }

   if( InputManager::GetInstance()->QuitGame() ||
      InputManager::GetInstance()->IsKeyPressed( SDLK_ESCAPE ) )
   {
      manager->QuitGame();
   }
}



void MenuState::Update( GameManager *manager )
{
      //ClickButton And Change State
      for( std::list< Button* >::reverse_iterator itr = m_buttonList.rbegin();
         itr != m_buttonList.rend();
         ++itr )
      {
         (*itr)->Update();
         if( ( *itr )->HasToQuit() )
         {
            manager->QuitGame();
            break;
         }
         else if( ( *itr )->HasToChangeState() )
         {
            manager->ChangeState( (*itr)->GetState() );
            break;
         }
      }
}