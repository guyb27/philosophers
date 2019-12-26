# include "hello.h"

typedef struct 				s_philo_gui
{
	SDL_Window		*sdl_window;
	SDL_Surface		*sdl_screen_surface;
	SDL_Surface 	*sdl_hello_world;
	SDL_Window		*window;
	SDL_Surface 	*screen_surface;
}							t_philo_gui;

bool ft_philo_sdl_error(const char *info, const char *err)
{
    printf("%s: %s", info, err);
    return (EXIT_FAILURE);
}

bool    ft_philo_sdl_init(t_philo_gui *philo_gui)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        return (ft_philo_sdl_error("SDL failed initialize", SDL_GetError()));

    //Create window
    philo_gui->sdl_window = SDL_CreateWindow( "Le diner des philosophes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP );

    if( philo_gui->sdl_window == NULL )
        return (ft_philo_sdl_error("SDL failed create window", SDL_GetError()));

    //Get window surface
    philo_gui->sdl_screen_surface= SDL_GetWindowSurface( philo_gui->sdl_window );

    return (EXIT_SUCCESS);
}

bool    ft_philo_sdl_load_media(t_philo_gui *philo_gui)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	philo_gui->sdl_hello_world = SDL_LoadBMP( "/Users/guillaumemadec/philosophers/assets/pictures/philo.bmp");
	if(philo_gui->sdl_hello_world == NULL)
        return (ft_philo_sdl_error("SDL failed to load image", SDL_GetError()));
	return (EXIT_SUCCESS);
}

void    ft_philo_sdl_close(t_philo_gui *philo_gui)
{
    //Deallocate surface
	SDL_FreeSurface(philo_gui->sdl_hello_world);
	philo_gui->sdl_hello_world = NULL;

	//Destroy window
	SDL_DestroyWindow(philo_gui->sdl_window);
	philo_gui->sdl_window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int ft_philo_sdl(void)
{
    t_philo_gui     philo_gui;

    ft_memset(&philo_gui, 0, sizeof(philo_gui));

	//Initialize SDL
	if (ft_philo_sdl_init(&philo_gui) == EXIT_FAILURE)
        return (ft_philo_sdl_error("SDL failed initialize", "ft_philo_sdl_init returned EXIT_FAILURE"));
    //Create window
    if (ft_philo_sdl_load_media(&philo_gui) == EXIT_FAILURE)
    {
        ft_philo_sdl_close(&philo_gui);
        return (ft_philo_sdl_error("SDL failed load media", "ft_philo_sdl_load_media returned EXIT_FAILURE"));
    }

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
    while( !quit )
    {
        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0)
        {
            //User requests quit
            if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN)
            {
                quit = true;
            }
        }  
        SDL_BlitSurface( philo_gui.sdl_hello_world, NULL, philo_gui.sdl_screen_surface, NULL );
        SDL_UpdateWindowSurface( philo_gui.sdl_window );
    }

    ft_philo_sdl_close(&philo_gui);
    return (0);
}
