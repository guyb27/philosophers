#include "../include/hello.h"

void	ft_get_locate(t_wand_location wand_locate[])
{
	wand_locate[0].x_window = 8;
	wand_locate[0].y_window = 70;
	wand_locate[0].number = 0;
	wand_locate[1].x_window = 15;
	wand_locate[1].y_window = 70;
	wand_locate[1].number = 1;
	wand_locate[2].x_window = 22;
	wand_locate[2].y_window = 70;
	wand_locate[2].number = 2;
	wand_locate[3].x_window = 28;
	wand_locate[3].y_window = 40;
	wand_locate[3].number = 3;
	wand_locate[4].x_window = 22;
	wand_locate[4].y_window = 10;
	wand_locate[4].number = 4;
	wand_locate[5].x_window = 15;
	wand_locate[5].y_window = 10;
	wand_locate[5].number = 5;
	wand_locate[6].x_window = 8;
	wand_locate[6].y_window = 10;
	wand_locate[6].number = 6;
}

t_philo_location	*ft_get_philo_locate(int wand_number)
{
	t_philo_location *locate;

	locate = ft_memalloc(sizeof(t_philo_location));
	if (wand_number == 0)
	{
		locate->x_capsule = 3;
		locate->y_capsule = 50;
	}
	else if (wand_number == 6)
	{
		locate->x_capsule = 10;
		locate->y_capsule = 5;
	}
	else if (wand_number == 1)
	{
		locate->x_capsule = 10;
		locate->y_capsule = 90;
	}
	else if (wand_number == 5)
	{
		locate->x_capsule = 17;
		locate->y_capsule = 5;
	}
	else if (wand_number == 2)
	{
		locate->x_capsule = 17;
		locate->y_capsule = 90;
	}
	else if (wand_number == 4)
	{
		locate->x_capsule = 24;
		locate->y_capsule = 10;
	}
	else if (wand_number == 3)
	{
		locate->x_capsule = 24;
		locate->y_capsule = 80;
	}
	return locate;
}
char **ft_get_philo_name(void)
{
	char **ret;

	ret = NULL;
	ft_malloc_cmd(&ret, "Platon");
	ft_malloc_cmd(&ret, "Aristote");
	ft_malloc_cmd(&ret, "Heraclite");
	ft_malloc_cmd(&ret, "Epictete");
	ft_malloc_cmd(&ret, "Marc-Aurele");
	ft_malloc_cmd(&ret, "Seneque");
	ft_malloc_cmd(&ret, "Socrate");
	return (ret);
}

e_ret_status	ft_can_you_do_eat(t_wand *left, t_wand *right, t_philo *data)
{
	int		ret_left = 0;
	int		ret_right = 0;

	//ret_left = pthread_mutex_destroy(&left->mutex);
	//ret_right = pthread_mutex_destroy(&right->mutex);
//	if (!ret_left && !ret_right)
//	{
		//left->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		ret_left = pthread_mutex_trylock(&left->mutex);
		//right->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		ret_right = pthread_mutex_trylock(&right->mutex);
//	}
	/*if (!ret_right)
	{
		//exit(1);
	}*/
	if (!ret_left && ret_right)
		return (LEFT);
	else if (ret_left && !ret_right)
		return (RIGHT);
	else if (ret_left && ret_right)
		return (NOTHING);
	else
		return (ALL);
}

int		ft_waiting(void (*function)(t_philo *philo), t_philo *data, size_t wait_time)
{
	size_t			begin_time;
	size_t			now_time;
	char *str;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	ft_actualize(data->capsule, "WAITING...", X_STATE, Y_STATE);
	while (now_time < begin_time + wait_time)
	{
		usleep(1000000);
		ft_actualize(data->capsule, "WAITING...", X_STATE, Y_STATE);
		function(data);
		ft_sprintf(&str, "");
		if (data->life <= 0)
		{
			printf("%s est MORT !\n", data->name);
			return (1);
		}
		time( (time_t*)&now_time );
	}
	return (0);
}

int		ft_eat(t_philo **data, t_philo_heart **philo)
{
	char *str;
	t_wand	*wand;
	size_t			begin_time;
	size_t			now_time;

	str = NULL;
	(*data)->state = TO_EAT;

	ft_actualize_wand((t_philo_heart**)&(*philo)->prev, EAT_LEFT);
	ft_actualize_wand((t_philo_heart**)&((*philo)->next), EAT_RIGHT);
//	((t_wand*)(*philo)->prev->data)->wand_state = EAT_LEFT;
//	((t_wand*)(*philo)->next->data)->wand_state = EAT_RIGHT;
//	ft_print_wand((*philo)->prev);
//	ft_print_wand((*philo)->next);
	ft_actualize((*data)->capsule, "MANGE", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", EAT_T);
	ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
	ft_strdel(&str);
	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + EAT_T)
	{
		usleep(1000000);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (begin_time + EAT_T) - now_time);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		ft_strdel(&str);
	}
	pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	wand = (t_wand*)(*philo)->next->data;
	wand->wand_state = EAT_LEFT;
	wand = (t_wand*)(*philo)->prev->data;
	wand->wand_state = EAT_RIGHT;
//	oo
	(*data)->life = MAX_LIFE;
	ft_sprintf(&str, "%d", MAX_LIFE);
	ft_actualize((*data)->capsule, str, X_LIFE, Y_LIFE);
	return (0);
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data)
{
	size_t			begin_time;
	size_t			now_time;
	char *str;
	t_wand	*wand;

	if (ret == LEFT)
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	else if (ret == RIGHT)
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	time( (time_t*)&begin_time );
	now_time = begin_time;
	ft_actualize((*data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", THINK_T);
	ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
	while (now_time < begin_time + THINK_T)
	{
		usleep(1000000);
		(*data)->life--;
		ft_sprintf(&str, "%d", (*data)->life);
		ft_actualize((*data)->capsule, str, X_LIFE, Y_LIFE);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			return (1);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (begin_time + THINK_T) - now_time);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		ft_strdel(&str);
	}
	return (0);
}

int		ft_eat_or_think(t_philo_heart **philo, t_philo **data)
{
	int ret, ret0, ret1;
	size_t			begin_time;
	size_t			now_time;
	char *str;
	t_wand	*wand;

	str = NULL;
	if ((ret = ft_can_you_do_eat((*philo)->prev->data, (*philo)->next->data, (*philo)->data)) == ALL)
		ft_eat(data, philo);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, philo, data);
	//A FAIRE:Prend une baguette qui peut etre prise par un philosophe qui veut manger
	return (0);
}

int		ft_rest(t_philo_heart **philo, t_philo **data)
{
	char *str;
	size_t			begin_time;
	size_t			now_time;

	str = NULL;
	(*data)->state = TO_REST;
	ft_actualize((*data)->capsule, "SE REPOSE", X_STATE, Y_STATE);
	ft_sprintf(&str, "%d", REST_T);
	ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
	ft_strdel(&str);
	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + REST_T)
	{
		(*data)->life = (*data)->life - 1;
		usleep(1000000);
		ft_sprintf(&str, "%d", (*data)->life);
		ft_actualize((*data)->capsule, str, X_LIFE, Y_LIFE);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%d", (int)((REST_T + begin_time) - now_time));
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		ft_strdel(&str);
		if (!(*data)->life)
		{
			ft_actualize((*data)->capsule, "IS DEAD", X_STATE, Y_STATE);
			return (1);
		}
	}
	return (0);
}

void	ft_print_baguette(t_philo_heart *heart)
{
	t_philo *philo;
	t_wand *wand;
	char	*str = NULL;

static int i = 0;
	wand = heart->data;
	philo = heart->prev->data;
	ft_sprintf(&str, "%s%sMID:[|]%s%s%s",
	philo->name,
	ft_strlen(philo->name) ? ":[ ], " : "",
	heart->next->type == PHILO ? ", " : "",
	heart->next->type == PHILO ? ((t_philo*)heart->next->data)->name : "",
	heart->next->type == PHILO ? ":[ ]" : "");
	ft_actualize(((t_wand*)heart->data)->capsule, str, 0, 0);
	ft_strdel(&str);
	i++;
}

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	t_philo			*data;
	char			*str;

	philo = (t_philo_heart*)arg;
	data = philo->data;
	while ((size_t)((t_philo*)philo->data)->life)
	{
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(&philo, &data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
			ft_rest(&philo, &data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(&philo, &data);
	}
	return ((void*)0);
}

void	ft_create_thread(t_philo_heart **philo_heart, char *str, t_philo_location locate)
{
	pthread_t		thread;
	t_philo_heart	*new_philo_heart;
	t_philo			*philo;
	t_wand			*wand;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	philo = ft_memalloc(sizeof(t_philo));
	ft_strcpy(philo->name, str);
	philo->state = TO_REST;
	philo->life = MAX_LIFE;
	new_philo_heart->type = PHILO;
	new_philo_heart->data = philo;
	while (1)
	{
		if ((*philo_heart)->type == WAND && (*philo_heart)->prev->type == WAND)
		{
			philo->locate = ft_get_philo_locate(((t_wand*)(*philo_heart)->prev->data)->locate->number);
			philo->capsule = ft_create_philo_window(philo);
			new_philo_heart->next = *philo_heart;
			new_philo_heart->prev = (*philo_heart)->prev;
			(*philo_heart)->prev->next = new_philo_heart;
			(*philo_heart)->prev = new_philo_heart;
		//	if ((*philo_heart)->prev->type == PHILO && (*philo_heart)->prev->prev->type == WAND)
		//		ft_print_baguette((*philo_heart)->prev->prev);
			break ;
		}
		*philo_heart = (*philo_heart)->next;
	}
	pthread_create (&thread, NULL, ft_philo, new_philo_heart);
	philo->thread = thread;
}

void	ft_create_wand(t_philo_heart **philo_heart, t_wand_location wand_locate)
{
	t_wand			*wand;
	t_philo_heart	*new_philo_heart;
	t_wand_location *locate;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	locate = ft_memalloc(sizeof(t_wand_location));
	locate->x_window = wand_locate.x_window;
	locate->y_window = wand_locate.y_window;
	locate->number = wand_locate.number;
	wand = ft_memalloc(sizeof(t_wand));
	new_philo_heart->type = WAND;
	wand->wand_state = FREE;
	//	wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//ft_bzero(&wand->mutex, sizeof(pthread_mutex_t));
	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	//wand->mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;//VERIF_ERROR
	pthread_mutex_lock(&g_mut);
	new_philo_heart->data = wand;
	wand->locate = locate;
	wand->wand_state = FREE;
	wand->capsule=subwin(stdscr, 1, 40, locate->x_window, locate->y_window);
	wbkgd(wand->capsule, COLOR_PAIR(2));
	pthread_mutex_unlock(&g_mut);
	if (!*philo_heart)
	{
		*philo_heart = new_philo_heart;
		new_philo_heart->prev = new_philo_heart;
		new_philo_heart->next = new_philo_heart;
	}
	else if (new_philo_heart->type == WAND)
	{
		new_philo_heart->next = *philo_heart;
		new_philo_heart->prev = (*philo_heart)->prev;
		(*philo_heart)->prev->next = new_philo_heart;
		(*philo_heart)->prev = new_philo_heart;
		*philo_heart  = (*philo_heart)->prev;
	}
//void	ft_print_wand(t_philo_heart *philo_heart)
//	ft_print_wand((*philo_heart)->prev->prev);
}

void	ft_waiting_to_twerk(void)
{
	size_t			begin_time;
	size_t			now_time;
	char			*str;
	int				key = 0;

	str = NULL;
	time( (time_t*)&begin_time );
	now_time = begin_time;
	pthread_mutex_lock(&g_mut);
	WINDOW *base;
	base = subwin(stdscr, 5, 25, 0, 92);
	wbkgd(base, COLOR_PAIR(2));
	wmove(base, 0, 0);
	wprintw(base, "MAX_LIFE: ");
	wprintw(base, ft_itoa(MAX_LIFE));
	wmove(base, 1, 0);
	wprintw(base, "EAT_TIME: ");
	wprintw(base, ft_itoa(EAT_T));
	wmove(base, 2, 0);
	wprintw(base, "REST_TIME: ");
	wprintw(base, ft_itoa(REST_T));
	wmove(base, 3, 0);
	wprintw(base, "THINK_TIME: ");
	wprintw(base, ft_itoa(THINK_T));
	wmove(base, 4, 0);
	wprintw(base, "TIME LEFT: ");
	wprintw(base, ft_itoa(TIMEOUT));
	wrefresh(base);
	pthread_mutex_unlock(&g_mut);
	while (now_time < begin_time + TIMEOUT)
	{
		usleep(1000000);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", TIMEOUT - (now_time - begin_time));
		ft_actualize(base, str, X_TIMEOUT, Y_TIMEOUT);
		ft_strdel(&str);
	}
	pthread_mutex_lock(&g_mut);
	clear();
	while (key != 27)
	{
		bkgd(COLOR_PAIR(2));
		usleep(1000000);
		refresh();
		key = getch();
		bkgd(COLOR_PAIR(3));
		usleep(1000000);
		refresh();
		bkgd(COLOR_PAIR(1));
		usleep(1000000);
		refresh();
	}
}

int main (void)
{
	t_philo_heart		*philo_heart;
	int					count;
	int					count2;
	char				**philo_name;
	t_philo				philo;
	t_philo_location	philo_locate[7];
	t_wand_location		wand_locate[7];

	pthread_mutex_init(&g_mut, NULL);
	ft_bzero(&philo_locate, sizeof(philo_locate));
	ft_bzero(&wand_locate, sizeof(wand_locate));
	philo_name = ft_get_philo_name();
	ft_get_locate(wand_locate);
	count = -1;
	count2 = -1;
	philo_heart = NULL;
	ft_init_curses();
	while (++count < NB_PHILO)
		ft_create_wand(&philo_heart, wand_locate[count]);
	//while(1);
	while (--count >= 0)
		ft_create_thread(&philo_heart, philo_name[count], philo_locate[count]);
	while (++count < NB_PHILO * 2)
	{
		if (philo_heart->type == WAND)
			ft_print_wand(&philo_heart);
		philo_heart = philo_heart->next;
	}
	/*while (++count < NB_PHILO * 2)
	  {
	  if (philo_heart->type == PHILO)
	  pthread_join (((t_philo*)philo_heart->data)->thread, NULL);
	  philo_heart = philo_heart->next;
	  }*/
	ft_waiting_to_twerk();
	endwin();
	ft_tabdel(&philo_name);
	return 0;
}
