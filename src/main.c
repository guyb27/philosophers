#include "../include/hello.h"

void	ft_get_wand_locate(t_wand_location locate[])
{
	locate[0].x_window = 8;
	locate[0].y_window = 70;
	locate[0].y_before = -1;
	locate[0].x_mid = 8;
	locate[0].y_mid = 75;
	locate[0].y_after = -1;
	locate[0].number = 0;
	locate[1].x_window = 15;
	locate[1].y_window = 70;
	locate[1].y_before = -1;
	locate[1].x_mid = 15;
	locate[1].y_mid = 75;
	locate[1].y_after = -1;
	locate[1].number = 1;
	locate[2].x_window = 22;
	locate[2].y_window = 70;
	locate[2].y_before = -1;
	locate[2].x_mid = 22;
	locate[2].y_mid = 75;
	locate[2].y_after = -1;
	locate[2].number = 2;
	locate[3].x_window = 28;
	locate[3].y_window = 40;
	locate[3].y_before = -1;
	locate[3].x_mid = 28;
	locate[3].y_mid = 40;
	locate[3].y_after = -1;
	locate[3].number = 3;
	locate[4].x_window = 22;
	locate[4].y_window = 10;
	locate[4].y_before = -1;
	locate[4].x_mid = 22;
	locate[4].y_mid = 10;
	locate[4].y_after = -1;
	locate[4].number = 4;
	locate[5].x_window = 15;
	locate[5].y_window = 10;
	locate[5].y_before = -1;
	locate[5].x_mid = 15;
	locate[5].y_mid = 10;
	locate[5].y_after = -1;
	locate[5].number = 5;
	locate[6].x_window = 8;
	locate[6].y_window = 10;
	locate[6].y_before = -1;
	locate[6].x_mid = 8;
	locate[6].y_mid = 10;
	locate[6].y_after = -1;
	locate[6].number = 6;
}

void	ft_get_philo_locate(t_wand *wand, t_philo_location *locate)
{
	if (wand->locate->number == 0)
	{
		locate->x_name = 3;
		locate->y_name = 50;
		locate->x_life = 4;
		locate->y_life = 50;
		locate->x_state = 5;
		locate->y_state = 50;
		locate->x_time = 6;
		locate->y_time = 50;
	}
	else if (wand->locate->number == 6)
	{
		locate->x_name = 10;
		locate->y_name = 5;
		locate->x_life = 11;
		locate->y_life = 5;
		locate->x_state = 12;
		locate->y_state = 5;
		locate->x_time = 13;
		locate->y_time = 5;
	}
	else if (wand->locate->number == 1)
	{
		locate->x_name = 10;
		locate->y_name = 90;
		locate->x_life = 11;
		locate->y_life = 90;
		locate->x_state = 12;
		locate->y_state = 90;
		locate->x_time = 13;
		locate->y_time = 90;
	}
	else if (wand->locate->number == 5)
	{
		locate->x_name = 17;
		locate->y_name = 5;
		locate->x_life = 18;
		locate->y_life = 5;
		locate->x_state = 19;
		locate->y_state = 5;
		locate->x_time = 20;
		locate->y_time = 5;
	}
	else if (wand->locate->number == 2)
	{
		locate->x_name = 17;
		locate->y_name = 90;
		locate->x_life = 18;
		locate->y_life = 90;
		locate->x_state = 19;
		locate->y_state = 90;
		locate->x_time = 20;
		locate->y_time = 90;
	}
	else if (wand->locate->number == 4)
	{
		locate->x_name = 24;
		locate->y_name = 10;
		locate->x_life = 25;
		locate->y_life = 10;
		locate->x_state = 26;
		locate->y_state = 10;
		locate->x_time = 27;
		locate->y_time = 10;
	}
	else if (wand->locate->number == 3)
	{
		locate->x_name = 24;
		locate->y_name = 80;
		locate->x_life = 25;
		locate->y_life = 80;
		locate->x_state = 26;
		locate->y_state = 80;
		locate->x_time = 27;
		locate->y_time = 80;
	}
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
	int		ret_left;
	int		ret_right;

	ret_left = pthread_mutex_destroy(&left->mutex);
	ret_right = pthread_mutex_destroy(&right->mutex);
	//ft_dprintf(2, "C_Y_D_E ret_left:[real:%d][%s] ret_right:[real:%d][%s], EBUSY:[%d], EINVAL:[%d]\n", ret_left,
//	ret_left == EBUSY ? "EBUSY(NOT INIT)" : "MUTEX INIT :)",
//	ret_right,
//	ret_right == EBUSY ? "EBUSY(NOT INIT)" : "MUTEX INIT :)",
//	EBUSY, EINVAL);
	if (!ret_left && !ret_right)
	{
		left->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		ret_left = pthread_mutex_trylock(&left->mutex);
		right->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		ret_right = pthread_mutex_trylock(&right->mutex);
	//wand->mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;//VERIF_ERROR
	}
	if (!ret_right)
	{
		////ft_dprintf(2, "MUTEX_ERROR\n");
		//exit(1);
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

void	ft_rest(t_philo *philo)
{
	philo->life--;
	//ft_dprintf(2, "REPOS [%s]:[%zi]PV--\n", philo->name, philo->life);
}

void	ft_think(t_philo *philo)
{
	philo->life--;
	////ft_dprintf(2, "THINK [%s]:[%zi]PV--\n", philo->name, philo->life);
}

int		ft_waiting(void (*function)(t_philo *philo), t_philo *data, size_t wait_time)
{
	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + wait_time)
	{
		//ft_dprintf(2, "now_time: [%zi], begin_time: [%zi]\n", now_time, begin_time);
		usleep(1000000);
		function(data);
		if (data->life <= 0)
		{
			printf("%s est MORT !\n", data->name);
			return (1);
		}
		time( (time_t*)&now_time );
	}
	return (0);
}

int		ft_eat_or_think(t_philo_heart *philo, t_philo	*data)
{
	int ret, ret0, ret1;
	t_wand	*wand;
	if ((ret = ft_can_you_do_eat(philo->prev->data, philo->next->data, philo->data)) == ALL)
	{
		//ft_dprintf(2, "\033[0;32m0[%s] mange\033[0;m\n", (char*)((t_philo*)philo->data)->name);
		/*move(data->locate.x_state, data->locate.y_state);
		printw("STATE: ");
		printw("MANGE");
		refresh();*/
		data->state = TO_EAT;
		data->life = MAX_LIFE;
		usleep(1000000 * EAT_T);
		ret0 = pthread_mutex_unlock(&((t_wand*)philo->prev->data)->mutex);
		ret1 = pthread_mutex_unlock(&((t_wand*)philo->next->data)->mutex);
		wand = (t_wand*)philo->next->data;
		wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		wand = (t_wand*)philo->prev->data;
		wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		//ft_dprintf(2, "\033[0;32m1[%s] mange 0:[%d] 1:[%d]\033[0;m\n", (char*)((t_philo*)philo->data)->name, ret0, ret1);
	}
	else if (ret == LEFT || ret == RIGHT)
	{
		//ft_dprintf(2, "0[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		/*data->state = TO_THINK;
		move(data->locate.x_state, data->locate.y_state);
		printw("STATE: ");
		printw("REFLECHIS");
		refresh();*/
		/**/

	size_t			begin_time;
	size_t			now_time;
	size_t			life = 0;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	life = (size_t)((t_philo*)philo->data)->life;
	while (now_time < begin_time + THINK_T)
	{
		usleep(1000000);
		life--;

/*		move(data->locate.x, data->locate.y_life);
		printw("LIFE POINTS: [");
		printw(ft_itoa(10));
		printw("/");
		printw(ft_itoa(MAX_LIFE));
		printw("]");
		refresh();*/
		if (!(size_t)((t_philo*)philo->data)->life)
		{
			//ft_dprintf(2, "[%s] EST MORT\n", (char*)((t_philo*)philo->data)->name);
			return (1);
		}
		time( (time_t*)&now_time );
	}
	if (ret == LEFT)
	{
		ret0 = pthread_mutex_unlock(&((t_wand*)philo->prev->data)->mutex);
		wand = (t_wand*)philo->prev->data;
		wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	}
	else if (ret == RIGHT)
	{
		ret1 = pthread_mutex_unlock(&((t_wand*)philo->next->data)->mutex);
		wand = (t_wand*)philo->next->data;
		wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	}

		/**/
//		if (ft_waiting(&ft_think, data, THINK_T))
//			return (1);
		//usleep(1000000 * THINK_T);
		//ft_dprintf(2, "1[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		//A FAIRE:Prend une baguette qui peut etre prise par un philosophe qui veut manger
	}
	else
	{
		//ft_dprintf(2, "\033[0;31mWAITING ... RET: [%d] !\033[0;m\n", ret);
		usleep(1000000);
		//ft_eat_or_think(philo, data);
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	t_philo			*data;
	size_t			*life;

	philo = (t_philo_heart*)arg;
	data = philo->data;
	life = &((t_philo*)philo->data)->life;
	while ((size_t)((t_philo*)philo->data)->life)
	{
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
		{
			//ft_dprintf(2, "0[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			data->state = TO_REST;
	/*	move(data->locate.x_state, data->locate.y_state);
		printw("STATE: ");
		printw("SE REPOSE");
		refresh();*/
			/**///

	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + REST_T)
	{
		*life = *life - 1;
		usleep(1000000);
	/*	move(data->locate.x_life, data->locate.y_life);
		printw("LIFE POINTS: [");
		printw(ft_itoa(*life));
		printw("/");
		printw(ft_itoa(MAX_LIFE));
		printw("]");
		refresh();*/
		//ft_dprintf(2, "[%s][ REPOS ]Perd une vie : [%zi]\n", (char*)((t_philo*)philo->data)->name, *life);
		//if (!(size_t)((t_philo*)philo->data)->life)
		if (!*life)
		{
	/*	move(data->locate.x_state, data->locate.y_state);
		printw("STATE: ");
		printw("IS DEAD");
		refresh();*/
			//ft_dprintf(2, "[%s] EST MORT DE REPOS\n", (char*)((t_philo*)philo->data)->name);
				return ((void*)1);
		}
		time( (time_t*)&now_time );
	}
			/**///
		//	if (ft_waiting(&ft_rest, data, REST_T))
		//		return ((void*)1);
			//usleep(1000000 * REST_T);
			//ft_dprintf(2, "1[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			//PASSE EN REPOS
		}
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
	}
//	}
	return ((void*)0);
}

void	ft_print_philo(t_philo *philo)
{
	move(philo->locate.x_name, philo->locate.y_name);
	printw("NAME: ");
	printw(philo->name);
	move(philo->locate.x_life, philo->locate.y_life);
	printw("LIFE POINTS: [");
	printw(ft_itoa(philo->life));
	printw("/");
	printw(ft_itoa(MAX_LIFE));
	printw("]");
	move(philo->locate.x_state, philo->locate.y_state);
	printw("STATE: ");
	printw(philo->state == TO_REST ? "SE REPOSE" : philo->state == TO_EAT ? "MANGE" : philo->state == TO_THINK ? "PENSE" : "UNKNOW");
	move(philo->locate.x_time, philo->locate.y_time);
	printw("TIME: ");
	printw(ft_itoa(philo->time));
	refresh();
}

void	ft_print_baguette(t_philo_heart *philo_heart)
{
	t_wand *wand;

	wand = (t_wand*)philo_heart->data;
	wand->locate->capsule=subwin(stdscr, 1, 50, wand->locate->x_window, wand->locate->y_window);
	wbkgd(wand->locate->capsule, COLOR_PAIR(2));
	wmove(wand->locate->capsule, 0, 0);
	wprintw(wand->locate->capsule, "MID:[|]");
	wrefresh(wand->locate->capsule);
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
			ft_get_philo_locate((*philo_heart)->data, &philo->locate);
			ft_print_philo(philo);
			wand = (*philo_heart)->prev->data;
//			wand->locate->y_after = wand->locate->y_mid + 9;
//			move(wand->locate->x_mid, wand->locate->y_mid + 7);
//			printw(", ");
//			printw(philo->name);
//			printw(":[");
//			printw(" ");
//			printw("]");
			wand = (*philo_heart)->data;
			wand->locate->y_before = wand->locate->y_mid;
			wand->locate->y_mid = wand->locate->y_before + ft_strlen(philo->name) + 6;
//			move(wand->locate->x_mid, wand->locate->y_before);
///			printw(philo->name);
//			printw(":[");
//			printw(" ");
//			printw("], MID:[");
//			printw("|");
//			printw("]");
			if (wand->locate->y_after > -1)
			{
//				printw(", ");
				wand->locate->y_after = wand->locate->y_mid + 9;
//				philo = (*philo_heart)->next->data;
//				printw(philo->name);
//				printw(":[");
//				printw(" ");
//				printw("]");
			}
			refresh();
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
//	locate->x_before = wand_locate.x_before;
	locate->y_before = wand_locate.y_before;
	locate->x_window = wand_locate.x_window;
	locate->y_window = wand_locate.y_window;
	locate->x_mid = wand_locate.x_mid;
	locate->y_mid = wand_locate.y_mid;
//	locate->x_after = wand_locate.x_after;
	locate->y_after = wand_locate.y_after;
	locate->number = wand_locate.number;
	locate->capsule=subwin(stdscr, 1, 40, locate->x_window, locate->y_window);
	wbkgd(locate->capsule, COLOR_PAIR(2));
	wmove(locate->capsule, 0, 0);
	wprintw(locate->capsule, "MID:[|]");
	wrefresh(locate->capsule);
	wand = ft_memalloc(sizeof(t_wand));
	new_philo_heart->type = WAND;
	wand->wand_state = FREE;
//	wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//ft_bzero(&wand->mutex, sizeof(pthread_mutex_t));
	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	//wand->mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;//VERIF_ERROR
	////ft_dprintf(2, "PTHREAD_MUTEX_INITIALIZER: [%d], PTHREAD_ERRORCHECK_MUTEX_INITIALIZER\n", (int)PTHREAD_MUTEX_INITIALIZER, (int)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER);
	new_philo_heart->data = wand;
	wand->locate = locate;
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
	while (now_time < begin_time + TIMEOUT)
	{
		usleep(1000000);
		time( (time_t*)&now_time );
		wmove(base, 4, 0);
		wclrtoeol(base);
		wprintw(base, "TIME LEFT: ");
		wprintw(base, ft_itoa(TIMEOUT - (now_time - begin_time)));
		wrefresh(base);
	}
	//ft_dprintf(2, "Now, it is time... To DAAAAAAAANCE ! ! !\n");
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

	ft_bzero(&philo_locate, sizeof(philo_locate));
	ft_bzero(&wand_locate, sizeof(wand_locate));
	philo_name = ft_get_philo_name();
	ft_get_wand_locate(wand_locate);
	count = -1;
	count2 = -1;
	philo_heart = NULL;
	ft_init_curses();
	move(0, 0);
	printw("A problem has been detected and windows been shut down to prevent damage to your computer.");
	move(1, 0);
	printw("UNMOUNTABLE_BOOT_VOLUME :");
	move(2, 0);
	printw("*** STOP: 0X89F1080ED (0X345A3BC5, 0X62348EB3A, 0X0967EAC4F0)");
	while (++count < NB_PHILO)
	{
		ft_create_wand(&philo_heart, wand_locate[count]);
		//ft_print_baguette(philo_heart);
	}
//	while (1);
	while (--count >= 0)
		ft_create_thread(&philo_heart, philo_name[count], philo_locate[count]);
	/*while (++count < NB_PHILO * 2)
	{
		if (philo_heart->type == WAND)
		{
			ft_print_baguette(philo_heart);
		}
		philo_heart = philo_heart->next;
	}*/
	/*//ft_dprintf(2, "COUNT: [%d]\n", count);
	count2 = -1;
	while (++count2 < NB_PHILO*2)
	{
		//ft_dprintf(2, "[%d] [%s]\n", philo_heart->n, philo_heart->type == PHILO ? "PHILO" : "WAND");
		philo_heart = philo_heart->next;
	}*/
	
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
