#pragma once
template< class T >
class Rect
{
public:
   Rect( T x = 0, T y = 0, T w = 0, T h = 0 ) :
      m_x( x ),
      m_y( y ),
      m_w( w ),
      m_h( h )
   {
   }

   ~Rect(){};

   T m_x;
   T m_y;
   T m_w;
   T m_h;
};

