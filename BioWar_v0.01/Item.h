#pragma once
#include "gameobject.h"
#include "Sprite.h"
class Item : public GameObject
{
public:

   enum ItemId
   {
      Health    = 1,
      NewWeapon = 2,
      Life      = 3
   };

   Item( Sprite * sprite, double x, double y, double w, double h, int ammoutOfHealth = 50 );
   ~Item(void);

   virtual int Update( int dt ){ return 0; };
   void Render( double cameraX, double cameraY );

   inline int GetAmmountOfHealth(){ return m_ammountOfHealth; }

protected:
   Sprite * m_sprite;
   uint16_t m_id;
   int      m_ammountOfHealth;
};

