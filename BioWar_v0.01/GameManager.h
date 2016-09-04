#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Sprite.h"
#include <vector>

class GameState;

class GameManager
{
public:
   GameManager();
   ~GameManager();
   void Run();

   int StackSize();
   void ChangeState( GameState *state );
   void PushState( GameState *state );
   void PopState();

   void QuitGame();
   
private:
   void render();
   void handleEvents();
   void update();

   Sprite * m_bg;
   bool m_isRunning;
   std::vector< GameState * > m_states;
};

#endif