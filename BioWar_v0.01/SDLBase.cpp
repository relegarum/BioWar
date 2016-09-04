#include "SDLBase.h"

SDL_Surface * SDLBase::s_screen;
SDL_Joystick * SDLBase::s_joystick;

int SDLBase::InitSDL()
{
   SDL_Init( SDL_INIT_EVERYTHING );
   if( TTF_Init() == - 1)
   {
      char * error = TTF_GetError();
      std::cerr << error << std::endl;
   }

   int soundFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
   if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1 ) {
      std::cerr << Mix_GetError()  << std::endl;
   }

   s_screen = SDL_SetVideoMode( MAX_WIDTH, MAX_HEIGHT, 32, SDL_SWSURFACE );
   SDL_WM_SetCaption( "B.I.O.W.A.R.S", "B.I.O.W.A.R.S" );
   
   SDL_JoystickEventState( SDL_ENABLE );
   if( ( s_joystick = SDL_JoystickOpen( 0 ) ) == NULL )
   {
      std::cerr << SDL_GetError() << std::endl;
   }

   TimerManager::GetInstance();

   return 0;
}

SDL_Joystick * SDLBase::GetJoystick()
{
   return s_joystick;
}

void SDLBase::FullScreen()
{
   s_screen = SDL_SetVideoMode( MAX_WIDTH, MAX_HEIGHT, 32, SDL_SWSURFACE | SDL_FULLSCREEN );
}

SDL_Surface * SDLBase::Clip( SDL_Surface * surface, SDL_Rect * clip )
{
   if( surface == NULL ||
       clip    == NULL )
   {
      std::cerr << "Surface or clip NULL" << std::endl;
      return NULL;
   }
   //format.de
   SDL_Surface * auxSurface = SDL_CreateRGBSurface( surface->flags, clip->w, clip->h, surface->format->BitsPerPixel, 0, 0, 0, 0 );
   SDL_BlitSurface( surface, clip, auxSurface, NULL );

   return auxSurface;
}

SDL_Surface * SDLBase::RotoZoomSurface( SDL_Surface * source, double angle, double scaleX, double scaleY )
{
   if( ( source == NULL ) ||
      ( scaleX <= 0 ) ||
      ( scaleY <= 0 ) )
   {
      std::cerr << "Surface equals NULL or scales lesser than 0" << std::endl;
      return NULL;
   }
   return rotozoomSurfaceXY( source, angle, scaleX, scaleY, 1 );
}

void SDLBase::PlayChunk( Mix_Chunk * chunk, int channel, int times )
{
   if( Mix_PlayChannel( channel, chunk, times ) == -1 )
   {
      std::cerr << Mix_GetError()  << std::endl;
   }
   return ;
}


// Move to some physics manager or something like that
bool SDLBase::CheckCollision( SDL_Rect &one, SDL_Rect &other )
{
   int leftObject, leftOther;
   int rightObject, rightOther;
   int topObject, topOther;
   int bottomObject, bottomOther;

   leftObject   = one.x;
   rightObject  = one.x + one.w;
   topObject    = one.y;
   bottomObject = one.y + one.h;

   leftOther   = other.x;
   rightOther  = other.x + other.w;
   topOther    = other.y;
   bottomOther = other.y + other.h;

   if( bottomObject <= topOther )
   {
      return false;
   }

   if( topObject >= bottomOther )
   {
      return false;
   }

   if( rightObject <= leftOther )
   {
      return false;
   }

   if( leftObject >= rightOther )
   {
      return false;
   }

   return true;
}


Mix_Music   * SDLBase::LoadMusic( std::string musicFileName )
{
   Mix_Music * music = Mix_LoadMUS( musicFileName.c_str() );
   if( music == NULL )
   {
      std::cerr << Mix_GetError()  << std::endl;
   }
   return music;
}

Mix_Chunk   * SDLBase::LoadChunk( std::string chunkFileName )
{
   Mix_Chunk * chunk = Mix_LoadWAV( chunkFileName.c_str() );
   if( chunk == NULL )
   {
      std::cerr << Mix_GetError()  << std::endl;
   }
   return chunk;
}

void SDLBase::Quit()
{
   TimerManager::Free();
   SDL_JoystickClose( s_joystick );
   TTF_Quit();
   SDL_Quit();
   while( Mix_Init(0) )
      Mix_Quit();
}

SDL_Surface *SDLBase::GetScreen()
{
   return s_screen;
}

SDL_Surface *SDLBase::LoadImage( std::string fileName, int alphaRed, int alphaGreen, int alphaBlue )
{
   SDL_Surface * optmizedImage = LoadImage( fileName );
   if( optmizedImage == NULL )
   {
      return optmizedImage;
   }

   Uint32 colorKey = SDL_MapRGB( optmizedImage->format, alphaRed, alphaGreen, alphaBlue );
   SDL_SetColorKey( optmizedImage, SDL_SRCCOLORKEY, colorKey );

   return optmizedImage;
}


TTF_Font * SDLBase::LoadFont( std::string fontFileName, uint16_t size )
{
   TTF_Font * fontSurface = TTF_OpenFont( fontFileName.c_str(), size );
   
   if( fontSurface == NULL )
   {
      char * error = TTF_GetError();
      std::cerr <<  error << std::endl;
   }
   
   return fontSurface;
}

SDL_Surface * SDLBase::LoadFontSurface( TTF_Font * font, std::string &text, SDL_Color &color )
{
   if( font == NULL )
   {
      std::cerr << "Font null" << std::endl;
   }

   SDL_Surface * message = TTF_RenderText_Solid( font, text.c_str(), color );
   if( message == NULL )
   {
      std::cerr << "Coudn't create the surface with the text LINE:" << __LINE__ << " FILE:" << __FILE__ << std::endl;
   }

   return message;
}

SDL_Surface *SDLBase::LoadImage( std::string fileName )
{
   SDL_Surface * image;
   SDL_Surface * optmizedImage;
   image = IMG_Load( fileName.c_str() );

   if( image == NULL )
   {
      return image;
   }

   if( image->format->Amask > 0 )
   {
      optmizedImage = SDL_DisplayFormatAlpha( image );
   }
   else
   {
      optmizedImage = SDL_DisplayFormat( image );
   }

   SDL_FreeSurface( image );

   return optmizedImage;
}

void SDLBase::RenderSurface(SDL_Surface * surface,SDL_Rect * clip ,SDL_Rect * dst, SDL_Surface * father )
{
   if( father == NULL )
      SDL_BlitSurface( surface, clip, s_screen, dst );
   else
      SDL_BlitSurface( surface, clip, father, dst );
}


void  SDLBase::RefreshScreen()
{

   SDL_Flip( s_screen );
   //std::string newString( "B.I.O.W.A.R.S" );
   //std::string concatString =  TimerManager::GetInstance()->GetFPS();

   //newString += concatString;
   //if( !concatString.empty() )
   //{
   //   SDL_WM_SetCaption( newString.c_str()  , NULL );
   //}
}

SDLBase::SDLBase()
{
}


SDLBase::~SDLBase()
{
}
