/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gui_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 13:37:43 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/23 13:55:49 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "hello.h"

bool    ft_philo_sdl_init(t_philo_gui *philo_gui)
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        return (ft_philo_sdl_error("SDL failed initialize", SDL_GetError()));

    //Create window
    philo_gui->sdl_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
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
	philo_gui->sdl_hello_world = SDL_LoadBMP( "/Users/dzonda/Dev/philosophers/assets/pictures/lac_en_montagne.bmp");
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