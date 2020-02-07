#include "../include/hello.h"

t_philo_location	*ft_get_philo_locate(int wand_number, int x, int y)
{
	t_philo_location *locate;

	ft_dprintf(2, "%sWAND_NUMBER: [%d]%s\n", GREEN, wand_number, STOP);
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
//	else
//		ft_dprintf(2, "%sPROBLEME GET_PHILO_LOCATE%s\n", RED, STOP);
	return (locate);
}

char *ft_store_philo_name(void)//OBSOLETE !!!
{
	char *ret;

	ft_sprintf(&ret, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s",
	"Platon", "Aristote", "Heraclite", "Epictete", "Marc-Aurele", "Seneque",
	"Socrate", "Descartes", "Diderot", "Fichte", "Nietzsche", "Marx",
	"Montaigne", "Montesquieu", "Rousseau", "Voltaire", "Freud", "Weber");
	return (ret);
}

char	*ft_get_name(void)
{
	static int	already_taken[NB_PHILO] = {0};
	char		*tmp_str;
	char		**philo_names;
	int			i;
	char		*str_ret;

	i = -1;
	str_ret = NULL;
	tmp_str = ft_store_philo_name();
	philo_names = ft_strsplit(tmp_str, ';');
//	pthread_mutex_lock(&g_mut);
	while (++i < NB_PHILO)
		if (already_taken[i] == 0)
		{
			already_taken[i] = 1;
			str_ret = ft_strdup(philo_names[i]);
			i = NB_PHILO;
		}
//	pthread_mutex_unlock(&g_mut);
	free(tmp_str);
	ft_tabdel(&philo_names);
	return (str_ret);
}

e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right, t_philo *data)
{
	int		ret_left;
	int		ret_right;

	ret_left = pthread_mutex_trylock(&left->mutex);
	ret_right = pthread_mutex_trylock(&right->mutex);
	if (!ret_left && ret_right)
		return (LEFT);
	else if (ret_left && !ret_right)
		return (RIGHT);
	else if (ret_left && ret_right)
		return (NOTHING);
	else
		return (ALL);
}

int		ft_eat(t_philo **data, t_philo_heart **philo)
{
	char			*str;
	size_t			begin_time;
	size_t			now_time;
	int				eat_t;

	eat_t = ft_handle_define(GET_INFOS, EAT, 0);
	str = NULL;
	begin_time = ft_eat_begin_actualize(philo);
	now_time = begin_time;
	while (now_time <= begin_time + eat_t && g_all_in_life)
	{
		usleep(SEC);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (int)((begin_time + eat_t) - now_time) > 0 ?
		(begin_time + eat_t) - now_time : 0);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			g_all_in_life = false;
	}
	ft_eat_end_actualize(philo);
	return (0);
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str[2];
	int				think_t;

	think_t = ft_handle_define(GET_INFOS, THINK, 0);
	begin_time = ft_think_begin_actualize(philo, ret);
	now_time = begin_time;
	//while (now_time <= begin_time + THINK_T && g_all_in_life)
	while (now_time <= begin_time + think_t && g_all_in_life)
	{
		usleep(SEC);
		(*data)->life--;
		time((time_t*)&now_time);
		//ft_sprintf(&str[0], "%zi", (int)((begin_time + THINK_T) - now_time) >
		ft_sprintf(&str[0], "%zi", (int)((begin_time + think_t) - now_time) >
		//0 ? (begin_time + THINK_T) - now_time : 0);
		0 ? (begin_time + think_t) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
		ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			g_all_in_life = false;
	}
	ft_think_end_actualize(philo, ret);
	return (0);
}

int		ft_eat_or_think(t_philo_heart **philo, t_philo **data)
{
	int ret;

	if ((ret = ft_can_you_do_eat((*philo)->prev->data, (*philo)->next->data,
	(*philo)->data)) == ALL)
		ft_eat(data, philo);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, philo, data);
	else
		return (1);
	return (0);
}

int		ft_rest(t_philo_heart **philo, t_philo **data)
{
	char			*str[2];
	size_t			begin_time;
	size_t			now_time;
	int				rest_t;

	rest_t = ft_handle_define(GET_INFOS, REST, 0);
	str[0] = NULL;
	str[1] = NULL;
	begin_time = ft_rest_begin_actualize(philo);
	now_time = begin_time;
	//while (now_time <= begin_time + REST_T && g_all_in_life)
	while (now_time <= begin_time + rest_t && g_all_in_life)
	{
		usleep(SEC);
		(*data)->life = (*data)->life - 1;
		ft_sprintf(&str[0], "%d", (*data)->life);
		time((time_t*)&now_time);
		//ft_sprintf(&str[1], "%zi", (int)((REST_T + begin_time) - now_time) > 0 ?
		ft_sprintf(&str[1], "%zi", (int)((rest_t + begin_time) - now_time) > 0 ?
		//(REST_T + begin_time) - now_time : 0);
		(rest_t + begin_time) - now_time : 0);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
		ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(*data)->life)
			g_all_in_life = false;
	}
	return (0);
}

void	ft_init_philo(void **arg, t_philo_heart **philo)
{
	t_screen_size		ss;

	getmaxyx(stdscr, ss.y, ss.x);
	//while (((t_philo_heart*)arg)->type != PHILO && !((t_philo*)((t_philo_heart*)arg)->data)->name)
	*philo = ((t_philo_heart*)(void*)arg);
	((t_philo*)(*philo)->data)->name = ft_get_name();
	((t_philo*)(*philo)->data)->state = TO_REST;
	((t_philo*)(*philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
}

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	char			*str;

	philo = (*(t_philo_mother**)arg)->heart;
	pthread_mutex_lock(&g_mut);
	while ((philo->type == PHILO && ((t_philo*)philo->data)->name) || philo->type == WAND)
			philo = philo->next;
	((t_philo*)(philo)->data)->name = ft_get_name();
	pthread_mutex_unlock(&g_mut);
	((t_philo*)(philo)->data)->state = TO_REST;
	((t_philo*)(philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
	((t_philo*)philo->data)->capsule = ft_create_philo_window(philo->data, arg);
	while ((size_t)((t_philo*)(philo)->data)->life && g_all_in_life)
	{
		if ((e_philo_state)((t_philo*)(philo)->data)->state == TO_EAT)
			ft_rest(&philo, (t_philo**)&philo->data);
		else
			if (ft_eat_or_think(&philo, (t_philo**)&(philo)->data))
			{
				usleep(SEC);
				((t_philo*)philo->data)->life = ((t_philo*)philo->data)->life - 1;
				ft_sprintf(&str, "%d", ((t_philo*)philo->data)->life);
				pthread_mutex_lock(&g_mut);
				ft_actualize(((t_philo*)philo->data)->capsule, str, X_LIFE, Y_LIFE);
				pthread_mutex_unlock(&g_mut);
				ft_strdel(&str);
			}
	}
	return ((void*)0);
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
	t_wand_location *locate;

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

void	ft_init_and_begin_game(t_screen_size ss)
{
	int count;
	pthread_t	thread;
	t_philo_heart		*philo_heart;
	t_philo_mother		*mother;
	WINDOW				*win;

	count = -1;
	g_all_in_life = true;
	philo_heart = NULL;
	mother = ft_memalloc(sizeof(t_philo_mother));
	mother->win = ft_memalloc(sizeof(t_philo_mother));
	mother->win = newwin(ss.y, ss.x, 0, 0);
	wbkgd(mother->win, COLOR_PAIR(1));
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		ft_create_wand(&philo_heart, ss);
	while (--count >= 0)
		ft_create_philo(&philo_heart, ss);
	mother->heart = philo_heart;
	for(int i = 0;i< NB_PHILO * 2;i++)
	{
	/*	if (mother->heart->type == PHILO)
		{
			ft_dprintf(2, "PHILO: x[%d], y:[%d]\n",
			((t_philo*)mother->heart->data)->locate->x_capsule,
			((t_philo*)mother->heart->data)->locate->y_capsule
			);
		}*/
		mother->heart = mother->heart->next;
	}
	while (++count < ft_handle_define(GET_INFOS, NBPHILO, 0))
		pthread_create(&thread, NULL, ft_philo, &mother);
	wrefresh(mother->win);
	count = 0;
	while (count < ft_handle_define(GET_INFOS, NBPHILO, 0))
	{
		if (philo_heart->type == WAND && !((t_wand*)philo_heart->data)->locate->init)
			count += ft_print_wand(philo_heart);
		philo_heart = (philo_heart)->next;
	}
	ft_main_loop(ft_print_game_var(ss), ss, &philo_heart);
	ft_print_game_var(ss);
}

void	ft_init_and_begin_main_menu(void)
{
	t_screen_size		ss;

	getmaxyx(stdscr, ss.y, ss.x);
	ft_menu(ss.x, ss.y);
	ft_init_and_begin_game(ss);
}

int main (int ac, char **av)
{
	if (ft_catch_error(ac, av))
		return (1);
	pthread_mutex_init(&g_mut, NULL);
	ft_init_curses();
	ft_init_and_begin_main_menu();
	return 0;
}
