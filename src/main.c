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
	wand_locate[6].number = 6;/*
								 locate->x_capsule = 3;
								 locate->y_capsule = 50;
								 locate->x_name = 3;
								 locate->y_name = 50;
								 locate->x_life = 4;
								 locate->y_life = 50;
								 locate->x_state = 5;
								 locate->y_state = 50;
								 locate->x_time = 6;
								 locate->y_time = 50;*/
}

t_philo_location	*ft_get_philo_locate(int wand_number)
{
	t_philo_location *locate;

	locate = ft_memalloc(sizeof(t_philo_location));
	if (wand_number == 0)
	{
		locate->x_capsule = 3;
		locate->y_capsule = 50;
		locate->x_name = 3;
		locate->y_name = 50;
		locate->x_life = 4;
		locate->y_life = 50;
		locate->x_state = 5;
		locate->y_state = 50;
		locate->x_time = 6;
		locate->y_time = 50;
	}
	else if (wand_number == 6)
	{
		locate->x_capsule = 10;
		locate->y_capsule = 5;
		locate->x_name = 10;
		locate->y_name = 5;
		locate->x_life = 11;
		locate->y_life = 5;
		locate->x_state = 12;
		locate->y_state = 5;
		locate->x_time = 13;
		locate->y_time = 5;
	}
	else if (wand_number == 1)
	{
		locate->x_capsule = 10;
		locate->y_capsule = 90;
		locate->x_name = 10;
		locate->y_name = 90;
		locate->x_life = 11;
		locate->y_life = 90;
		locate->x_state = 12;
		locate->y_state = 90;
		locate->x_time = 13;
		locate->y_time = 90;
	}
	else if (wand_number == 5)
	{
		locate->x_capsule = 17;
		locate->y_capsule = 5;
		locate->x_name = 17;
		locate->y_name = 5;
		locate->x_life = 18;
		locate->y_life = 5;
		locate->x_state = 19;
		locate->y_state = 5;
		locate->x_time = 20;
		locate->y_time = 5;
	}
	else if (wand_number == 2)
	{
		locate->x_capsule = 17;
		locate->y_capsule = 90;
		locate->x_name = 17;
		locate->y_name = 90;
		locate->x_life = 18;
		locate->y_life = 90;
		locate->x_state = 19;
		locate->y_state = 90;
		locate->x_time = 20;
		locate->y_time = 90;
	}
	else if (wand_number == 4)
	{
		locate->x_capsule = 24;
		locate->y_capsule = 10;
		locate->x_name = 24;
		locate->y_name = 10;
		locate->x_life = 25;
		locate->y_life = 10;
		locate->x_state = 26;
		locate->y_state = 10;
		locate->x_time = 27;
		locate->y_time = 10;
	}
	//else if (wand->locate->number == 3)
	else if (wand_number == 3)
	{
		locate->x_capsule = 24;
		locate->y_capsule = 80;
		locate->x_name = 24;
		locate->y_name = 80;
		locate->x_life = 25;
		locate->y_life = 80;
		locate->x_state = 26;
		locate->y_state = 80;
		locate->x_time = 27;
		locate->y_time = 80;
	}
	return locate;
}
char **ft_get_philo_name(void)
{
	char **ret;

	ret = NULL;
	ft_malloc_cmd(&ret, "Platon");
	ft_malloc_cmd(&ret, "Aristote");
	ft_malloc_cmd(&ret, "Héraclite");
	ft_malloc_cmd(&ret, "Epictète");
	ft_malloc_cmd(&ret, "Marc-Aurèle");
	ft_malloc_cmd(&ret, "Sénèque");
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
		ft_dprintf(2, "MUTEX_ERROR\n");
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
		//////ft_dprintf(2, "now_time: [%zi], begin_time: [%zi]\n", now_time, begin_time);
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
	//wand = (t_wand*)(*philo)->next->data;
	//wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//wand = (t_wand*)(*philo)->prev->data;
	//wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	(*data)->life = MAX_LIFE;
	ft_sprintf(&str, "%d", MAX_LIFE);
	ft_actualize((*data)->capsule, str, X_LIFE, Y_LIFE);
	return (0);
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data)
{
	size_t			begin_time;
	size_t			now_time;
	size_t			life = 0;
	char *str;
	t_wand	*wand;

	if (ret == LEFT)
	{
		pthread_mutex_unlock(&((t_wand*)(*philo)->prev->data)->mutex);
	//	wand = (t_wand*)(*philo)->prev->data;
	//	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	}
	else if (ret == RIGHT)
	{
		pthread_mutex_unlock(&((t_wand*)(*philo)->next->data)->mutex);
	//	wand = (t_wand*)(*philo)->next->data;
	//	wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	}
	time( (time_t*)&begin_time );
	now_time = begin_time;
	life = (size_t)((t_philo*)(*philo)->data)->life;
	ft_actualize((*data)->capsule, "REFLECHIS", X_STATE, Y_STATE);
	ft_sprintf(&str, "%zi", THINK_T);
	ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
	while (now_time < begin_time + THINK_T)
	{
		usleep(1000000);
		life--;
		ft_sprintf(&str, "%d", life);
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

int		ft_eat_or_think(t_philo_heart *philo, t_philo	*data)
{
	int ret, ret0, ret1;
	size_t			begin_time;
	size_t			now_time;
	char *str;
	t_wand	*wand;

	str = NULL;
	if ((ret = ft_can_you_do_eat(philo->prev->data, philo->next->data, philo->data)) == ALL)
		ft_eat(&data, &philo);
	else if (ret == LEFT || ret == RIGHT)
		ft_think(ret, &philo, &data);
	//A FAIRE:Prend une baguette qui peut etre prise par un philosophe qui veut manger
	else
	{
		//////ft_dprintf(2, "\033[0;31mWAITING ... RET: [%d] !\033[0;m\n", ret);
		usleep(1000000);
		//ft_eat_or_think(philo, data);
	}
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

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	t_philo			*data;
	size_t			*life;
	char			*str;

	philo = (t_philo_heart*)arg;
	data = philo->data;
	life = &((t_philo*)philo->data)->life;
	while ((size_t)((t_philo*)philo->data)->life)
	{
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
			ft_rest(&philo, &data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
	}
	return ((void*)0);
}

WINDOW	*ft_create_philo_window(t_philo *philo)
{
	WINDOW *capsule;

	pthread_mutex_lock(&g_mut);
	capsule = subwin(stdscr, 4, 25, philo->locate->x_capsule, philo->locate->y_capsule);
	wbkgd(capsule, COLOR_PAIR(3));
	wmove(capsule, 0, 0);
	wprintw(capsule, "NAME: ");
	wprintw(capsule, philo->name);
	wmove(capsule, 1, 0);
	wprintw(capsule, "LIFE POINTS: ");
	wprintw(capsule, ft_itoa(philo->life));
	wmove(capsule, 2, 0);
	wprintw(capsule, "STATE: ");
	wprintw(capsule, philo->state == TO_REST ? "SE REPOSE" : philo->state == TO_EAT ? "MANGE" : philo->state == TO_THINK ? "PENSE" : "UNKNOW");
	wmove(capsule, 3, 0);
	wprintw(capsule, "TIME: ");
	wprintw(capsule, ft_itoa(philo->time));
	wrefresh(capsule);
	pthread_mutex_unlock(&g_mut);
	return (capsule);
}

void	ft_print_baguette(t_philo_heart *heart)
{
	t_philo *philo;
	t_wand *wand;

	wand = heart->data;
	philo = heart->prev->data;
	pthread_mutex_lock(&g_mut);
	wmove(wand->capsule, 0, 0);
	wclrtoeol(wand->capsule);
	wprintw(wand->capsule, philo->name);
	wprintw(wand->capsule,":[ ], MID:[|]");
	if (heart->next->type == PHILO)
	{
		philo = heart->next->data;
		wprintw(wand->capsule, ", ");
		wprintw(wand->capsule, philo->name);
		wprintw(wand->capsule, ":[ ]");
	}
	wrefresh(wand->capsule);
	pthread_mutex_unlock(&g_mut);
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
			philo->locate = ft_get_philo_locate(((t_wand*)(*philo_heart)->data)->locate->number);
			philo->capsule = ft_create_philo_window(philo);
			new_philo_heart->next = *philo_heart;
			new_philo_heart->prev = (*philo_heart)->prev;
			(*philo_heart)->prev->next = new_philo_heart;
			(*philo_heart)->prev = new_philo_heart;
			ft_print_baguette(*philo_heart);
			ft_print_baguette((*philo_heart)->prev->prev);
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
	////////ft_dprintf(2, "PTHREAD_MUTEX_INITIALIZER: [%d], PTHREAD_ERRORCHECK_MUTEX_INITIALIZER\n", (int)PTHREAD_MUTEX_INITIALIZER, (int)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER);
	new_philo_heart->data = wand;
	wand->locate = locate;
	pthread_mutex_lock(&g_mut);
	wand->capsule=subwin(stdscr, 1, 40, locate->x_window, locate->y_window);
	wbkgd(wand->capsule, COLOR_PAIR(2));
	wmove(wand->capsule, 0, 0);
	wprintw(wand->capsule, "MID:[|]");
	wrefresh(wand->capsule);
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
}

void	ft_waiting_to_twerk(void)
{
	size_t			begin_time;
	size_t			now_time;

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
		pthread_mutex_lock(&g_mut);
		wmove(base, 4, 0);
		wclrtoeol(base);
		wprintw(base, "TIME LEFT: ");
		wprintw(base, ft_itoa(TIMEOUT - (now_time - begin_time)));
		wrefresh(base);
		pthread_mutex_unlock(&g_mut);
	}
	//////ft_dprintf(2, "Now, it is time... To DAAAAAAAANCE ! ! !\n");
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
	while (--count >= 0)
		ft_create_thread(&philo_heart, philo_name[count], philo_locate[count]);
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
