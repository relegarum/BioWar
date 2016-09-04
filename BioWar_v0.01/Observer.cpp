#include "Observer.h"


Observer::Observer( GameEntity * entity )
{
   m_subject = entity;
}


Observer::~Observer(void)
{
}


GameEntity* Observer::GetEntity()
{
   return m_subject;
}