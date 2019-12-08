#include "hello.h"

void hello(void)
{
	ft_printf("Hello World\n");
}
					

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
/*
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//    
//    //The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//
//    //The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;
*/
bool init_sdl(SDL_Window **sdl_window, SDL_Surface **sdl_screenSurface)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//                                                    //Create window
		*sdl_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( sdl_window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			*sdl_screenSurface = SDL_GetWindowSurface( *sdl_window );
		}
	}

	return success;
}

bool loadMedia(SDL_Surface **sdl_hello_world)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	*sdl_hello_world = SDL_LoadBMP( "/Users/gmadec/nm-otools/assets/pictures/lac_en_montagne.bmp" );
	if( *sdl_hello_world == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "../assets/pictures/lac_en_montagne.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close_sdl(SDL_Window **sdl_window, SDL_Surface **sdl_hello_world)
{
	//Deallocate surface
	SDL_FreeSurface( *sdl_hello_world );
	*sdl_hello_world = NULL;

	//            //Destroy window
	SDL_DestroyWindow( *sdl_window );
	*sdl_window = NULL;

	//                        //Quit SDL subsystems
	SDL_Quit();
}
