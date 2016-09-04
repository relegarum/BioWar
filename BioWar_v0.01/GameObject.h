#pragma once
#include "Rect.h"

class GameObject
{
public:
   enum ObjectClass
   {
      Obstacle      = 1,
      Damage        = 2,
      MainCharacter = 3
   };

   GameObject( double x, double y, double w, double h );
   virtual ~GameObject();

   virtual int  Update( int dt ) = 0;
   virtual void Render( double cameraX, double cameraY ) = 0;
   bool         CollidesWith( GameObject * other );

   // Interface 
   double GetX() const;
   void SetX( const double x );
   double GetY() const;
   void SetY( const double y );

   inline Rect< double > GetRectBox(){ return m_box; }

protected:
   Rect< double > m_box;
   double         m_x;
   double         m_y;      

   double         m_exceedBot;
   double         m_exceedTop;
   double         m_exceedLeft;
   double         m_exceedRight;
};

