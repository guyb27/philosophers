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
	char *str;
	t_wand	*wand;
	size_t			begin_time;
	size_t			now_time;

	str = NULL;
	begin_time = ft_eat_begin_actualize(philo);
	now_time = begin_time;
	while (now_time <= begin_time + EAT_T)
	{
		usleep(1000000);
		time( (time_t*)&now_time );
		ft_sprintf(&str, "%zi", (int)((begin_time + EAT_T) - now_time) > 0 ?
		(begin_time + EAT_T) - now_time : 0);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str, X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str);
	}
	ft_eat_end_actualize(philo);
	return (0);
}

int		ft_think(int ret, t_philo_heart **philo, t_philo **data)
{
	size_t			begin_time;
	size_t			now_time;
	char *str[2];
	t_wand	*wand;

	begin_time = ft_think_begin_actualize(philo, ret);
	now_time = begin_time;
	while (now_time <= begin_time + THINK_T)
	{
		usleep(1000000);
		(*data)->life--;
		time((time_t*)&now_time);
		ft_sprintf(&str[0], "%zi", (int)((begin_time + THINK_T) - now_time) > 0 ?
		(begin_time + THINK_T) - now_time : 0);
		ft_sprintf(&str[1], "%d", (*data)->life);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str[0], X_TIME, Y_TIME);
		ft_actualize((*data)->capsule, str[1], X_LIFE, Y_LIFE);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(size_t)((t_philo*)(*philo)->data)->life)
			return (1);
	}
	ft_think_end_actualize(philo, ret);
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
	return (0);
}

int		ft_rest(t_philo_heart **philo, t_philo **data)
{
	char *str[2];
	size_t			begin_time;
	size_t			now_time;
	int test = 0;

	str[0] = NULL;
	str[1] = NULL;
	begin_time = ft_rest_begin_actualize(philo);
	now_time = begin_time;
	while (now_time <= begin_time + REST_T)
	{
		usleep(1000000);
		(*data)->life = (*data)->life - 1;
		time((time_t*)&now_time);
		ft_sprintf(&str[0], "%d", (*data)->life);
		test = ((REST_T + begin_time) - now_time);
		test = test < 0 ? 0 : test;
		//ft_sprintf(&str[1], "%zi", test);
		ft_sprintf(&str[1], "%zi", (int)((REST_T + begin_time) - now_time) > 0 ?
		(REST_T + begin_time) - now_time : 0);
		pthread_mutex_lock(&g_mut);
		ft_actualize((*data)->capsule, str[0], X_LIFE, Y_LIFE);
		ft_actualize((*data)->capsule, str[1], X_TIME, Y_TIME);
		pthread_mutex_unlock(&g_mut);
		ft_strdel(&str[0]);
		ft_strdel(&str[1]);
		if (!(*data)->life)
		{
			pthread_mutex_lock(&g_mut);
			ft_actualize((*data)->capsule, "IS DEAD", X_STATE, Y_STATE);
			pthread_mutex_unlock(&g_mut);
			return (1);
		}
	}
	return (0);
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
//		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
//			ft_eat_or_think(&philo, &data);
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
			ft_rest(&philo, &data);
		else// if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
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
		pthread_mutex_lock(&g_mut);
		ft_actualize(base, str, X_TIMEOUT, Y_TIMEOUT);
		pthread_mutex_unlock(&g_mut);
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
