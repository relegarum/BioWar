#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameManager.h"

class GameState
{
public:
   virtual void Init() = 0;
   virtual void CleanUp() = 0;

   virtual void Pause() = 0;
   virtual void Resume() = 0;

   virtual void GainFocus( GameManager *manager ) = 0;
   virtual void HandleEvents( GameManager * manager ) = 0;
   virtual void Update( GameManager * manager ) = 0;

   inline void ChangeState( GameManager *game, GameState *state ) {  game->ChangeState( state ); }

protected:
   GameState() {}
};

#endif

