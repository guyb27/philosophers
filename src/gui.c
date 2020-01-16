/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gui.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 11:44:43 by dzonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/23 13:53:50 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "hello.h"

bool ft_philo_sdl_error(const char *info, const char *err)
{
    printf("%s: %s", info, err);
    return (EXIT_FAILURE);
}
/*
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
}*/
