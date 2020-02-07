#include "../include/hello.h"

void	ft_get_locate(t_wand_location **locate, int x, int y, int *n_time)
//FAIRE UN ALGO POUR DEFINIR LA TAILLE
{
	if (*n_time < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		*locate = ft_memalloc(sizeof(t_wand_location));
		if (*n_time == 0)
		{
			(*locate)->x_window = 7;
			(*locate)->y_window = (int)(x * 0.75) - 20;
			(*locate)->number = 0;
		}
		else if (*n_time == 1)
		{
			(*locate)->x_window = 14;
			(*locate)->y_window = (int)(x * 0.75) - 20;
			(*locate)->number = 1;
		}
		else if (*n_time == 2)
		{
			(*locate)->x_window = 21;
			(*locate)->y_window = (int)(x * 0.75) - 20;
			(*locate)->number = 2;
		}
		else if (*n_time == 3)
		{
			(*locate)->x_window = 28;
			(*locate)->y_window = (int)(x * 0.5) - 20;
			(*locate)->number = 3;
		}
		else if (*n_time == 4)
		{
			(*locate)->x_window = 21;
			(*locate)->y_window = (int)(x * 0.25) - 20;
			(*locate)->number = 4;
		}
		else if (*n_time == 5)
		{
			(*locate)->x_window = 14;
			(*locate)->y_window = (int)(x * 0.25) - 20;
			(*locate)->number = 5;
		}
		else if (*n_time == 6)
		{
			(*locate)->x_window = 7;
			(*locate)->y_window = (int)(x * 0.25) - 20;
			(*locate)->number = 6;
		}
		*n_time = *n_time + 1;
	}
	else
		*locate = NULL;
}

void		ft_handle_wand_location(t_wand_location **locate, e_handle_static_function h, t_screen_size ss)
{
	static int		n_time = 0;

	if (h == GET_INFOS)
		ft_get_locate(locate, ss.x, ss.y, &n_time);
	else if (h == INIT)
		n_time = 0;
}
