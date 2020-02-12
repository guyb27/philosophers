#include "../include/hello.h"

t_philo_location	*ft_get_philo_locate(int wand_number, int x, int y)
{
	(void)y;//A VOIR !
	t_philo_location *locate;

	locate = ft_memalloc(sizeof(t_philo_location));
	if (wand_number == 0)
	{
		locate->x_capsule = 2;
		//locate->x_capsule = 2 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.5) - 10;
	}
	else if (wand_number == 6)
	{
		locate->x_capsule = 9;
		//locate->x_capsule = 9 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.25) - 10;
	}
	else if (wand_number == 1)
	{
		locate->x_capsule = 9;
		//locate->x_capsule = 9 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.75) - 10;
	}
	else if (wand_number == 5)
	{
		locate->x_capsule = 16;
		//locate->x_capsule = 16 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.25) - 10;
	}
	else if (wand_number == 2)
	{
		locate->x_capsule = 16;
		//locate->x_capsule = 16 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.75) - 10;
	}
	else if (wand_number == 4)
	{
		locate->x_capsule = 23;
		//locate->x_capsule = 23 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.30) - 10;
	}
	else if (wand_number == 3)
	{
		locate->x_capsule = 23;
		//locate->x_capsule = 23 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.70) - 10;
	}
	locate->init = false;
	return (locate);
}

char *ft_store_philo_name(void)
{
	char *ret;

	ft_sprintf(&ret, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s",
			"Platon", "Aristote", "Heraclite", "Epictete", "Marc-Aurele", "Seneque",
			"Socrate", "Descartes", "Diderot", "Fichte", "Nietzsche", "Marx",
			"Montaigne", "Montesquieu", "Rousseau", "Voltaire", "Freud", "Weber");
	return (ret);
}

char	*ft_get_name(e_handle_static_function h)
{
	static int	already_taken[7] = {0};//A REMPLACER PAR LA FONCTION POUR LE NOMBRE DE FONCTION
	char		*tmp_str;
	char		**philo_names;
	int			i;
	char		*str_ret;

	i = -1;
	str_ret = NULL;
	if (h == INIT)
	{
		ft_bzero(already_taken, sizeof(already_taken));
		return (NULL);
	}
	tmp_str = ft_store_philo_name();
	philo_names = ft_strsplit(tmp_str, ';');
	while (++i < ft_handle_define(GET_INFOS, NBPHILO, 0))
		if (already_taken[i] == 0)
		{
			already_taken[i] = 1;
			str_ret = ft_strdup(philo_names[i]);
			i = ft_handle_define(GET_INFOS, NBPHILO, 0);
		}
	free(tmp_str);
	ft_tabdel(&philo_names);
	return (str_ret);
}

e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right, t_philo *data)
{
	int		ret_left;
	int		ret_right;

	(void)data;// A DEL
	if (left->locate->number % 2)
	{
		ret_left = pthread_mutex_trylock(&left->mutex);
		ret_right = pthread_mutex_trylock(&right->mutex);
	}
	else
	{
		ret_right = pthread_mutex_trylock(&right->mutex);
		ret_left = pthread_mutex_trylock(&left->mutex);
	}
	if (!ret_left && ret_right)
		return (LEFT);
	else if (ret_left && !ret_right)
		return (RIGHT);
	else if (ret_left && ret_right)
		return (NOTHING);
	else
		return (ALL);
}

int		ft_eat(t_philo **data, t_philo_heart **philo, t_philo_mother **mother)
{
	char			*str;
	size_t			begin_time;
	size_t			now_time;
	int				eat_t;

	eat_t = ft_handle_define(GET_INFOS, EAT, 0);
	str = NULL;
	begin_time = ft_eat_begin_actualize(philo, mother);
	now_time = begin_time;
	while (now_time <= begin_time + eat_t && (*mother)->all_in_life)
	{
		if (eat_t > 0)
			usleep(SEC);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (int)((begin_time + eat_t) - now_time) > 0 ?
				(begin_time + eat_t) - now_time : 0);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			(*mother)->all_in_life = false;
	}
	ft_eat_end_actualize(philo, mother);
	return (0);
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str[2];
	int				think_t;

	think_t = ft_handle_define(GET_INFOS, THINK, 0);
	begin_time = ft_think_begin_actualize(philo, ret, mother);
	now_time = begin_time;
	while (now_time <= begin_time + think_t && (*mother)->all_in_life)
	{
		if (think_t > 0)
		{
			usleep(SEC);
			(*data)->life--;
		}
		time((time_t*)&now_time);
		ft_sprintf(&str[0], "%zi", (int)((begin_time + think_t) - now_time) >
				0 ? (begin_time + think_t) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
		ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			(*mother)->all_in_life = false;
	}
	ft_think_end_actualize(philo, ret, mother);
	return (0);
}

int		ft_eat_or_think(t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	int ret;

	if ((ret = ft_can_you_do_eat((*philo)->prev->data, (*philo)->next->data,
					(*philo)->data)) == ALL)
		ft_eat(data, philo, mother);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, philo, data, mother);
	else
		return (1);
	return (0);
}

int		ft_rest(t_philo_heart **philo, t_philo **data, t_philo_mother **mother)
{
	char			*str[2];
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	str[0] = NULL;
	str[1] = NULL;
	begin_time = ft_rest_begin_actualize(philo, mother);
	now_time = begin_time;
	while (now_time <= begin_time + rest_t && (*mother)->all_in_life)
	{
		if (rest_t > 0)
		{
			usleep(SEC);
			(*data)->life = (*data)->life - 1;
		}
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
				(rest_t + begin_time) - now_time : 0);
		pthread_mutex_lock(&g_gmutex);
		ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
		ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(*data)->life)
			(*mother)->all_in_life = false;
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	char			*str;

	philo = (*(t_philo_mother**)arg)->heart;
	pthread_mutex_lock(&g_gmutex);
	while ((philo->type == PHILO && ((t_philo*)philo->data)->name) || philo->type == WAND)
		philo = philo->next;
	((t_philo*)(philo)->data)->name = ft_get_name(GET_INFOS);
	pthread_mutex_unlock(&g_gmutex);
	((t_philo*)(philo)->data)->state = TO_REST;
	((t_philo*)(philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
	((t_philo*)philo->data)->capsule = ft_create_philo_window(philo->data, arg, true);
	while ((size_t)((t_philo*)(philo)->data)->life && (*(t_philo_mother**)arg)->all_in_life)
	{
		ft_dprintf(2, "000FT_PHILO MOTHER_ADDR: [%p], HEART_ADDR: [%p]\n", arg,&(*(t_philo_mother**)arg)->heart );
		if ((e_philo_state)((t_philo*)(philo)->data)->state == TO_EAT)
			ft_rest(&philo, (t_philo**)&philo->data, arg);
		else
			if (ft_eat_or_think(&philo, (t_philo**)&(philo)->data, arg))
			{
				usleep(SEC);
				((t_philo*)philo->data)->life = ((t_philo*)philo->data)->life - 1;
				ft_sprintf(&str, "%d", ((t_philo*)philo->data)->life);
				pthread_mutex_lock(&g_gmutex);
				ft_actualize(((t_philo*)philo->data)->capsule, str, X_LIFE, Y_LIFE);
				pthread_mutex_unlock(&g_gmutex);
				ft_strdel(&str);
			}
	}
	return (__DARWIN_NULL);
}

void	ft_create_philo(t_philo_heart **philo_heart, t_screen_size ss)
{
	t_philo_heart	*new_philo_heart;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->type = PHILO;
	new_philo_heart->data = ft_memalloc(sizeof(t_philo));
	while (1)
	{
		if ((*philo_heart)->type == WAND &&
				(*philo_heart)->prev->type == WAND)
		{
			((t_philo*)new_philo_heart->data)->locate = ft_get_philo_locate(((t_wand*)(*philo_heart)->prev->data)->locate->number, ss.x, ss.y);
			new_philo_heart->next = *philo_heart;
			new_philo_heart->prev = (*philo_heart)->prev;
			(*philo_heart)->prev->next = new_philo_heart;
			(*philo_heart)->prev = new_philo_heart;
			break ;
		}
		*philo_heart = (*philo_heart)->next;
	}
}

void	ft_create_wand(t_philo_heart **philo_heart, t_screen_size ss)
{
	t_wand			*wand;
	t_philo_heart	*new_philo_heart;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->type = WAND;
	wand = ft_memalloc(sizeof(t_wand));
	wand->wand_state = FREE;
	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ft_handle_wand_location(&wand->locate, GET_INFOS, ss);
	new_philo_heart->data = wand;
	if (!*philo_heart)
	{
		*philo_heart = new_philo_heart;
		new_philo_heart->prev = new_philo_heart;
		new_philo_heart->next = new_philo_heart;
	}
	else
	{
		new_philo_heart->next = *philo_heart;
		new_philo_heart->prev = (*philo_heart)->prev;
		(*philo_heart)->prev->next = new_philo_heart;
		(*philo_heart)->prev = new_philo_heart;
		*philo_heart  = (*philo_heart)->prev;
	}
}

void	*ft_handle_mother_addr(void *mother, e_handle_static_function h)
{
	static void	*store_mother = NULL;

	if (h == INIT)
		store_mother = mother;
	else if (h == GET_INFOS)
		return (store_mother);
	return (NULL);
}

void	ft_init_and_begin_game(void)
{
	int					count;
	pthread_t			thread;
	t_philo_heart		*philo_heart;
	t_philo_mother		*mother;

	count = -1;
	philo_heart = NULL;
	mother = ft_memalloc(sizeof(t_philo_mother));
	ft_handle_mother_addr(&mother, INIT);
	mother->all_in_life = ft_handle_define(GET_INFOS, LIFE, 0) > 0 ? true : false;
	ft_dprintf(2, "LIFE: [%d]\n", mother->all_in_life ? 1 : 0);
	getmaxyx(stdscr, mother->ss.y, mother->ss.x);
	ft_get_name(INIT);
	ft_handle_wand_location(NULL, INIT, mother->ss);
	mother->win = newwin(mother->ss.y, mother->ss.x, 0, 0);
	wbkgd(mother->win, COLOR_PAIR(1));
	wrefresh(mother->win);
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		ft_create_wand(&philo_heart, mother->ss);
	while (--count >= 0)
		ft_create_philo(&philo_heart, mother->ss);
	mother->heart = philo_heart;
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		pthread_create(&thread, NULL, ft_philo, &mother);
		pthread_detach(thread);
	}
	count = 0;
	while (count < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		if (philo_heart->type == WAND && !((t_wand*)philo_heart->data)->locate->init)
			count += ft_print_wand(philo_heart, mother, true);
		philo_heart = (philo_heart)->next;
	}
	ft_print_game_var(mother, true);
	ft_main_loop(&mother);
}

void	ft_init_and_begin_main_menu(void)
{
	ft_menu();
	ft_init_and_begin_game();
}

void		ft_actualize_game(t_philo_mother **mother)
{
	t_philo_heart *heart;

	pthread_mutex_lock(&g_gmutex);
	heart = (*mother)->heart;
	delwin((*mother)->win_game_var);
	for (int i = 0, j = ft_handle_define(GET_INFOS, NBPHILO, 0) * 2; i < j;i++)
	{
		if (heart->type == PHILO)
		{
			delwin(((t_philo*)heart->data)->capsule);
		}
		else
		{
			delwin(((t_wand*)heart->data)->capsule);
		}
		heart = heart->next;
	}
	if ((*mother)->state_game)
		delwin((*mother)->state_game);
	free((*mother)->win);
	touchwin(stdscr);
	refresh();
	endwin();
	ft_init_curses();
	(*mother)->win = newwin((*mother)->ss.y, (*mother)->ss.x, 0, 0);
/*	getmaxyx((*mother)->ss.y, (*mother)->ss.x);
	ft_handle_wand_location(NULL, INIT, (*mother)->ss);
	//ft_handle_wand_location(&heart->->locate, GET_INFOS, (*mother)->ss);
	(*mother)->win = newwin((*mother)->ss.y, (*mother)->ss.x, 0, 0);
	wbkgd((*mother)->win, COLOR_PAIR(1));
	wrefresh((*mother)->win);
*/	while (mother);
	ft_print_game_var(*mother, false);
//	while (*mother);
	pthread_mutex_unlock(&g_gmutex);
}

void		ft_resize(int sig)// /!\ N'a pas sa place dans le menu vu que c est global
{
	void *mother_addr;

	if (sig != SIGWINCH)
		return ;
	mother_addr = ft_handle_mother_addr(NULL, GET_INFOS);
	if (mother_addr)
	{
		ft_dprintf(2, "000MOTHER_ADDR: [%p], HEART_ADDR: [%p]\n", mother_addr,&(*(t_philo_mother**)mother_addr)->heart );
		ft_actualize_game((t_philo_mother**)mother_addr);
		ft_dprintf(2, "1111MOTHER_ADDR: [%p], HEART_ADDR: [%p]\n", mother_addr,&(*(t_philo_mother**)mother_addr)->heart );
		ft_dprintf(2, "GAME: RESIZE_addr:[%p]\n", mother_addr);
	}
	else if (ft_handle_main_menu(GET_INFOS, 0, true, NULL))
	{
		ft_handle_main_menu(ACTUALIZE_SCREEN, 0, true, NULL);
		ft_dprintf(2, "MAIN_MENU: RESIZE\n");
	}
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
