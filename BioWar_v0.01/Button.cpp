#include "Button.h"
#include "InputManager.h"
#include "GameObject.h"


Button::Button( Sprite *sprite, double x, double y, double w, double h ) : 
   GameObject( x, y, w, h ),
   m_inside( false ),
   m_insideFirstTime( true ),
   m_quitGame( false )
{   
}

Button::Button( Sprite *sprite, GameState *state, double x, double y, double w, double h, Text * text ) : 
   GameObject( x, y, w, h ),
   m_sprite( sprite ),
   m_state( state ),
   m_inside( false ),
   m_insideFirstTime( true ),
   m_quitGame( false ),
   m_changeState( false )
{
   m_text = text;
   m_text->SetPos( ( m_x + m_sprite->GetWidth()/2 - m_text->GetSurface()->w/2 ), ( m_y + m_sprite->GetHeight()/4 - m_text->GetSurface()->h/2 ) );

   m_clips[0].m_x = 0;
   m_clips[0].m_y = 0;
   m_clips[0].m_h = m_sprite->GetHeight()/2; 
   m_clips[0].m_w = m_sprite->GetWidth();
   
   m_clips[1].m_x = 0;
   m_clips[1].m_y = m_sprite->GetHeight()/2;
   m_clips[1].m_h = m_sprite->GetHeight()/2;
   m_clips[1].m_w = m_sprite->GetWidth();

   m_sprite->Clip( m_clips[ 0 ] );

   m_insideChunk = new Sound( "sfx/change_menu.wav" );
   m_clickChunk  = new Sound( "sfx/high.wav" );
}

Button::~Button()
{
   if( m_clickChunk != NULL )
   {
      delete m_clickChunk;
   }
   if( m_insideChunk != NULL )
   {
      delete m_insideChunk;
   }
}

void Button::PlaySoundFX()
{
   if( m_inside )
   {
   }
   else
   {
   }
}

// Planet Methods
bool Button::IsInside( int x, int y )
{
   if( x >= m_x &&
      x < m_x + m_sprite->GetWidth()  &&
      y >= m_y &&
      y < m_y + m_sprite->GetHeight()/2 )
   {
      return true;
   }

   return false;
}

int Button::Update()
{
   if( m_inside )
   {
      if( m_insideFirstTime )
      {
         m_insideFirstTime = false;
         m_insideChunk->Play();
      }
      m_sprite->Clip( m_clips[1] );
   }
   else
   {
      m_insideFirstTime = true;
      m_sprite->Clip( m_clips[0] );
   }

   return 0;
}

void Button::InputHandle()
{
   int x;
   int y;
   InputManager::GetInstance()->GetMousePos( x, y );
   if( InputManager::GetInstance()->IsMouseDown( SDL_BUTTON_LEFT ) )
   {
      //ClickButton And Change State
      m_clickChunk->Play();
      if( IsInside( x, y ) )
      {
         if( m_text->GetText() == "Quit Game" )
         {
            InputManager::GetInstance()->SetQuitGame();
            m_quitGame = true;
         }
         m_changeState = true;
      }
   }
   else
   {
      if( IsInside( x, y ) )
      {
         SetFocus( true );
      }
      else
      {
         SetFocus( false );
      }
   }
   
}

void Button::Render( double cameraX, double cameraY )
{
   m_text->Render( 0, 0 );
   m_sprite->Render( m_x - cameraX, m_y - cameraY );
}