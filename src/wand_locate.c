#include "../include/hello.h"

static void	ft_get_locate(t_wand_location **locate, int x, int *n_time)
{
	if (*n_time < ft_handle_define(GET_INFOS, NBPHILO, 0) && g_gmode == ALL_WINDOWS)
	{
		*locate = ft_memalloc(sizeof(t_wand_location));
		if (*n_time == 0 || *n_time == 6)
			(*locate)->x_window = 7;
		else if (*n_time == 1 || *n_time == 5)
			(*locate)->x_window = 14;
		else if (*n_time == 4 || *n_time == 2)
			(*locate)->x_window = 21;
		else if (*n_time == 3)
			(*locate)->x_window = 28;
		if (*n_time < 3)
			(*locate)->y_window = (int)(x * 0.75) - 20;
		else if (*n_time == 3)
			(*locate)->y_window = (int)(x * 0.5) - 20;
		else if (*n_time < 7)
			(*locate)->y_window = (int)(x * 0.25) - 20;
		(*locate)->number = *n_time;
		*n_time = *n_time + 1;
	}
	else
		*locate = NULL;
}

void		ft_handle_wand_location(t_wand_location **locate, e_handle_static_function h, t_screen_size ss)
{
	static int		n_time = 0;

	if (h == GET_INFOS)
		ft_get_locate(locate, ss.x, &n_time);
	else if (h == INIT)
		n_time = 0;
}
