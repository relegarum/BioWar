#include "GameEntity.h"


GameEntity::GameEntity( double x, double y, double w, double h, int hitPoints, GameEntity::EntityId id ) :
   GameObject( x, y, w, h ),
   m_maxHitPoints( hitPoints ),
   m_actualHitPoints( hitPoints ),
   m_entityId( id )
{
}


void GameEntity::ChangeHitPoints( int damage )
{
   m_actualHitPoints -= damage;
}

void GameEntity::Render( double cameraX, double cameraY )
{
   m_animationMap[ m_label ]->Render( m_x - cameraX, m_y - cameraY );
}

void GameEntity::AddAnimation( uint16_t label, std::shared_ptr< Animation >& animation )
{
   m_animationMap[ label ] = animation;
}
