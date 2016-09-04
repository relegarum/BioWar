#include "GameObject.h"
#include <math.h>
#include "SDLBase.h"

GameObject::GameObject( double x, double y, double w, double h ):
   m_x( x ),
   m_y( y ),
   m_exceedBot( 0 ),
   m_exceedLeft( 0 ),
   m_exceedRight( 0 ),
   m_exceedTop( 0 )
{
   m_box.m_x = x;
   m_box.m_y = y;
   m_box.m_w = w;
   m_box.m_h = h;
}

bool GameObject::CollidesWith( GameObject * other )
{
   int leftObject   = m_x;
   int rightObject  = m_x + m_box.m_w;
   int topObject    = m_y;
   int bottomObject = m_y + m_box.m_h;

   int leftOther   = other->GetX();
   int rightOther  = other->GetX() + other->GetRectBox().m_w;
   int topOther    = other->GetY();
   int bottomOther = other->GetY() + other->GetRectBox().m_h;

   if( bottomObject <= topOther )
      return false;
   if( topObject >= bottomOther )
      return false;
   if( rightObject <= leftOther )
      return false;
   if( leftObject >= rightOther )
      return false;

   return true;
}

GameObject::~GameObject(void)
{
}

//Implementação
double GameObject::GetX() const
{
   return m_x;
}

void GameObject::SetX( const double x )
{
   m_x = x;
}
double GameObject::GetY() const
{
   return m_y;
}

void GameObject::SetY( const double y )
{
   m_y = y;
}
//Fim da implementação