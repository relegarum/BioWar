#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

int FPS = 50;    // Assign a FPS
int NextTick , interval ;

// Initialize FPS_Fn( )
void FPS_Initial(void) {
NextTick = 0 ;
interval = 1 * 1000 / FPS ; 
return;
}

// Frame Per Second Function  , put this in a loop
void FPS_Fn(void) {
if ( NextTick > SDL_GetTicks( ) ) SDL_Delay( NextTick - SDL_GetTicks( ) );
NextTick = SDL_GetTicks( ) + interval ;
return;
}

// This function load a image file to a surface
// Set bCKey with colorkey (R,G,B) to clear a color on the image
// Set alpha value for transparency 0(No transparent) ~ 255(Ivisible)
inline SDL_Surface *ImgLoader(char *file,bool bCKey, int r , int g , int b , int alpha)
{
	SDL_Surface *pic;
	pic = IMG_Load(file); // From SDL_image.h , load the image to pic
	// Log error message into stderr.txt if happened
	if(pic==NULL) fprintf(stderr,"Missing image %s : %s\n",file,IMG_GetError());
	if( bCKey ) {
		// Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.
		SDL_SetColorKey(pic,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic->format,r,g,b));
 		}
	if(alpha) SDL_SetAlpha(pic, SDL_SRCALPHA|SDL_RLEACCEL , 255 - alpha);
	pic = SDL_DisplayFormat(pic);
	return (pic);
}

// Load a normal picture into a surface
inline SDL_Surface *ImgLoader(char *file)       
				{ return ImgLoader(file,1,0,0,0,0) ; }
// Load a pic & set the transparent color to (255,255,255) , no alpha
inline SDL_Surface *ImgLoader(char *file,bool bCKey)
				{ return ImgLoader(file,1,255,255,255,0) ; }


int main(int argc, char *argv[])
{

SDL_Event event;
bool bRun = 1;
int pidx = 0 , aTick = 0;
SDL_Surface *screen ;
enum walk { justice1 , justice2 , justice3 , justice4 
	, justice5 , justice6 , justice_No  };
SDL_Surface *anim[justice_No];
SDL_Rect animRect ;
animRect.x = 160 ;
animRect.y = 160 ;

atexit(SDL_Quit);

if( SDL_Init(SDL_INIT_VIDEO) < 0 ) exit(1);

SDL_WM_SetCaption("SDL Window", NULL);

screen = SDL_SetVideoMode( 400 , 300 , 32 , SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_ANYFORMAT);

anim[0] = ImgLoader("./anim/justice1.gif",1,255,255,255,0);
anim[1] = ImgLoader("./anim/justice2.gif",1,255,255,255,0);
anim[2] = ImgLoader("./anim/justice3.gif",1,255,255,255,0);
anim[3] = ImgLoader("./anim/justice4.gif",1);
anim[4] = ImgLoader("./anim/justice5.gif",1);
anim[5] = ImgLoader("./anim/justice6.gif",1);

FPS_Initial( );

// Inilialize SDL_mixer , exit if fail
if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
// Setup audio mode
Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
Mix_Music *mus , *mus2 ;  // Background Music 
Mix_Chunk *wav , *wav2 ;  // For Sounds
mus = Mix_LoadMUS("./mixer/ff2prlde.mid");
mus2 = Mix_LoadMUS("./mixer/aria.mp3");
wav = Mix_LoadWAV("./mixer/po_p2k.wav");
wav2 = Mix_LoadWAV("./mixer/start.wav");
Mix_PlayMusic(mus,1); //Music loop=1

while(bRun) {
	aTick++;
	SDL_FillRect(screen , NULL , 0x221122);
	SDL_BlitSurface( anim[pidx] , NULL , screen , &animRect );
	SDL_Flip(screen);
    FPS_Fn();
	if( aTick%10 == 0 ) pidx++;
	if(pidx >= justice_No) pidx = 0;
	while( SDL_PollEvent( &event ) ){
		switch( event.type ){
			case SDL_KEYDOWN:
				//use -1 for the first free unreserved channel , 0-> no loop
				Mix_PlayChannel(-1,wav,0); 
				switch( event.key.keysym.sym ){
					case SDLK_UP:
						animRect.y = animRect.y - 10;
						break;
					case SDLK_DOWN:
						animRect.y = animRect.y + 10;
						break;
					case SDLK_LEFT:
						animRect.x = animRect.x - 10;
						break;
					case SDLK_RIGHT:
						animRect.x = animRect.x + 10;
						break;
					case SDLK_1:
						Mix_PlayMusic(mus,1); //Music loop=1
						break;
					case SDLK_2:
						Mix_PlayMusic(mus2,2); //Music loop=twice
						break;
					case SDLK_ESCAPE:
						bRun = 0 ;
						break;
					default:
						//use -1 for the first free unreserved channel , 0-> no loop
						Mix_PlayChannel(-1,wav2,0); 
						break;
					} // switch( event.key.keysym.sym ){ END
				break; // case SDL_KEYDOWN: END
			case SDL_QUIT:
				bRun = 0;
				break;
			default:
				break;
			} // switch( event.type ){ END
		} // while( SDLK_PollEvent( &event ) ){ END
	}; // while(bRun) { END

Mix_FreeChunk(wav);
Mix_FreeChunk(wav2);
Mix_FreeMusic(mus);
Mix_FreeMusic(mus2);
return 0;
}
