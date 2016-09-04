#pragma once

#include "GameObject.h"
#include "Animation.h"
#include <map>
#include <memory>

class GameEntity : public GameObject
{
public:

   enum EntityId
   {
      W3L2NId = 0,
      EnemyId = 1,
      ShootId = 2
   };

   using AnimationMap = std::map < uint16_t, std::shared_ptr< Animation > > ;
   GameEntity( double x, double y, double w, double h, int hitPoints, EntityId id );
   ~GameEntity() = default;

   int  Update( int dt ) = 0;
   void Render( double cameraX, double cameraY );

   void AddAnimation( uint16_t label, std::shared_ptr< Animation >& animation );
   AnimationMap& GetAnimationMap(){ return m_animationMap; }

   virtual void ChangeHitPoints( int damage );
   inline int  GetMaxPoints(){ return m_maxHitPoints; }
   inline int  GetHitPoints(){ return m_actualHitPoints; }
   inline uint16_t GetId(){ return m_entityId; }

protected:
   EntityId      m_entityId;
   int           m_actualHitPoints;
   int           m_maxHitPoints;
   double        m_velX;
   double        m_velY;
   uint16_t      m_label;
   AnimationMap  m_animationMap;
};

