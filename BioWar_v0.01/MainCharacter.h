#pragma once
#include "GameEntity.h"
#include <vector>
#include "Observer.h"
#define SHOOTING_GAP 300

class MainCharacter : public GameEntity
{
public:
   const double JumpingBaseSpeed;
   const double High;
   const double HurtSpeed;
   const double HurtHigh;

   enum Status
   {
      RIGHT    = 0,
      LEFT     = 1,
      JUMPING  = 1 << 2,
      SHOOTING = 1 << 3,
      HURTED   = 1 << 4,
      VICTORY  = 1 << 5,
      DEATH    = 1 << 6
   };

   enum ShootingTypes
   {
      NOSHOOT = 0,
      SIMPLE  = 1,
      CHARGED = 2
   };
   
   MainCharacter( double x, double y, double w, double h, int hitPoints );
   ~MainCharacter();
   
   void InputHandle();
   int  Update( int dt );

   void RAUL();
   bool Finish();
   bool Loose();

   bool CollidesWith( GameObject *  other );
   bool CollidesWithEntity( GameEntity * other );
   void CheckGroundCollision( double cameraX, double m_cameraY );

   double GetVelX() const;
   void SetVelX( const double velX );
   double GetVelY() const;
   void SetVelY( const double velY );

   void SetJumpAcceleration( double acc );
   void SetFalling( bool falling );
   short CreateShoot();
   int  GetDirection();
   bool GetIsJumping();
   void HandleCollision();
   void HandleCollision( GameObject * object );

   void AdjustPosition();
   unsigned short ShootType();

   void ChangeHitPoints( int damage );

   void AttachObserver( Observer * observer );
   void DetachObserver( Observer * observer );

protected:
   bool     m_falling;
   bool     m_gettinHurt;
   double   m_jumpAcceleration;
   float    m_offset;
   int      m_frame;
   int      m_status;
   bool     m_createShoot;
   short    m_shootForce;
   uint16_t m_shotType;   

   int m_hurtingTime;

   Timer            m_shootingTimer;
   Timer            m_chargeTimer;
   Timer            m_hurtingTimer;
   Timer            m_victoryTimer;
   Timer            m_deathTimer;
   Timer            m_changingWeaponTimer;

   Rect< double >              m_collisionBox;
   std::vector< Observer * >   m_observerPool;
   bool     m_jumping;

   double   m_velX;
   double   m_velY;     
      
};




