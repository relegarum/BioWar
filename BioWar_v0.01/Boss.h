#pragma once
#include "Enemy.h"
#include "Observer.h"
#include <vector>

class Boss : public Enemy, public Observer
{
public:

   enum class Behavior
   {
      SHOOTING,
      ROLL,
      MISSILING
   };

typedef void (*function_ptr)(int dt); // function pointer type
typedef std::map< Behavior, function_ptr> state_map;

   enum State
   {
      LEFT    = 0,
      RIGHT   = 1,
      ROLLING = 2
   };

   Boss( GameEntity * entity, double x, double y, double w, double h, int hitPoints = 500, int damage = 5 );
   ~Boss(void);

   int Update( int dt );
   void AlertAndUpdate();

   bool CreateMissil();
   bool CreateShoot();

   short GetDirection(){ return m_direction; }
   void ChangeHitPoints( double damage );

   void AttachObserver( Observer * observer );

private:
   std::vector< Observer * > m_observerPool;
   state_map m_behaviorMap;

   Behavior m_behavior;


   void updateRoll( int dt );
   void updateShooting( int dt );
   void updateMissiling( int dt );
   

   short m_direction;

   // Roll variables
   double m_rollVelX;
   double m_targetRoll;
   bool   m_reachedRollTarget;
   bool   m_rollTargetDefined;
   int    m_noRollingTime;
   Timer  m_noRollingTimer;
   
   // Missiling variables
   bool   m_createMissil;
   double m_targetMissil;
   int    m_missilingTime;
   Timer  m_missilingTimer;

   // Shooting variables
   double m_shottingVariables;
   int    m_shottingTime;
   bool   m_createShoot;
   Timer  m_shottingTimer;
};

