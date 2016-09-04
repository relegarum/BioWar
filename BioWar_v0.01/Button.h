#pragma once
#include "Sprite.h"
#include "Text.h"
#include "GameState.h"
#include "GameObject.h"
#include "Sound.h"

class Button : public GameObject
{
public:

   // C++11
   enum class ButtonType
   {
      ChangeStateButton,
      ActionButton
   };

   Button( Sprite *sprite, double x, double y, double w, double h );
   Button( Sprite *sprite, GameState *state, double x, double y, double w, double h, Text * text = NULL );
   ~Button();

   // Button Methods
   void PlaySoundFX();
   bool IsInside( int x, int y );
   
   void Render( double cameraX =  0.0, double cameraY = 0.0 );
   
   /// Melhorar isso
   int  Update();
   int  Update( int dt ){  return 0; };
   void InputHandle();

   inline bool HasToChangeState(){ return m_changeState; };

   inline Text* GetText(){ return m_text; }

   inline void SetFocus( const bool inside ){ m_inside = inside; }
   inline int GetFocus(){ return m_inside; }

   inline void SetState( GameState * state ){ m_state = state; }
   inline GameState * GetState(){ return m_state; };

   inline Sprite * GetSprite(){ return m_sprite; }


   inline bool HasToQuit() { return m_quitGame; };

private:
   Sprite    *    m_sprite;
   Text      *    m_text;
   GameState *    m_state;
   bool           m_inside;
   bool           m_insideFirstTime; 
   Sound     *    m_insideChunk;
   Sound     *    m_clickChunk;
   Rect< double > m_clips[2];
   bool           m_changeState;

   // Melhorar
   bool        m_quitGame;
};

