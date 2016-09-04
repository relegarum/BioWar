#pragma once
#include "gameobject.h"
#include "Animation.h"

class Obstacle : public GameObject
{
public:
   Obstacle( Animation * animation, double x, double y, double w, double h );
   ~Obstacle(void);

   int Update( int dt );
   void Render( double cameraX, double cameraY );
protected:
   Sprite * m_animation;
};

