#include "Item.h"


Item::Item( Sprite * sprite, double x, double y, double w, double h, int ammoutOfHealth ):
   GameObject( x, y, w, h ),
   m_sprite( sprite ),
   m_ammountOfHealth( ammoutOfHealth )
{
}


void Item::Render( double cameraX, double cameraY )
{
   m_sprite->Render( m_x - cameraX, m_y - cameraY );
}

Item::~Item(void)
{
}
