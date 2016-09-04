#pragma once

class GameEntity;

class Observer
{
public:
   Observer( GameEntity *entity );
   ~Observer();

   virtual void AlertAndUpdate() = 0;
protected:
   GameEntity* GetEntity();

   GameEntity * m_subject;
};

