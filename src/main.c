#include "../include/hello.h"

void	*ft_handle_mother_addr(void *mother, e_handle_static_function h)
{
	static void	*store_mother = NULL;

	if (h == INIT)
		store_mother = mother;
	else if (h == GET_INFOS)
		return (store_mother);
	return (NULL);
}

void	ft_init_and_begin_main_menu(void)
{
	ft_menu();
	ft_init_and_begin_game();
}

void		ft_actualize_game(void)
{
	pthread_mutex_lock(&g_gmutex);
	g_gmode = NOTHING_WINDOW;
	bkgd(COLOR_PAIR(2));
	refresh();
	pthread_mutex_unlock(&g_gmutex);
}

void		ft_resize(int sig)// /!\ N'a pas sa place dans le menu vu que c est global
{
	void *mother_addr;

	if (sig != SIGWINCH)
		return ;
	mother_addr = ft_handle_mother_addr(NULL, GET_INFOS);
	if (mother_addr)
		ft_actualize_game();
	else if (ft_handle_main_menu(GET_INFOS, 0, true, NULL))
		ft_handle_main_menu(ACTUALIZE_SCREEN, 0, true, NULL);
}

int main (int ac, char **av)
{
	if (ft_catch_error(ac, av))
		return (1);
	g_gmode = NOT_INIT;
	signal(SIGWINCH, ft_resize);
	pthread_mutex_init(&g_gmutex, NULL);
	ft_init_curses();
	ft_init_and_begin_main_menu();
	pthread_mutex_destroy(&g_gmutex);
	return 0;
}
