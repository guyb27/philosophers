#include "../include/hello.h"

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
	ft_printf("C_Y_D_E ret_left:[real:%d][%s] ret_right:[real:%d][%s], EBUSY:[%d], EINVAL:[%d]\n", ret_left,
	ret_left == EBUSY ? "EBUSY(NOT INIT)" : "MUTEX INIT :)",
	ret_right,
	ret_right == EBUSY ? "EBUSY(NOT INIT)" : "MUTEX INIT :)",
	EBUSY, EINVAL);
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
		//ft_printf("MUTEX_ERROR\n");
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
	ft_printf("REPOS [%s]:[%zi]PV--\n", philo->name, philo->life);
}

void	ft_think(t_philo *philo)
{
	philo->life--;
	//ft_printf("THINK [%s]:[%zi]PV--\n", philo->name, philo->life);
}

int		ft_waiting(void (*function)(t_philo *philo), t_philo *data, size_t wait_time)
{
	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + wait_time)
	{
		ft_printf("now_time: [%zi], begin_time: [%zi]\n", now_time, begin_time);
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
		ft_printf("\033[0;32m0[%s] mange\033[0;m\n", (char*)((t_philo*)philo->data)->name);
		data->state = TO_EAT;
		data->life = MAX_LIFE;
		usleep(1000000 * EAT_T);
		ret0 = pthread_mutex_unlock(&((t_wand*)philo->prev->data)->mutex);
		ret1 = pthread_mutex_unlock(&((t_wand*)philo->next->data)->mutex);
		wand = (t_wand*)philo->next->data;
		wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		wand = (t_wand*)philo->prev->data;
		wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
		ft_printf("\033[0;32m1[%s] mange 0:[%d] 1:[%d]\033[0;m\n", (char*)((t_philo*)philo->data)->name, ret0, ret1);
	}
	else if (ret == LEFT || ret == RIGHT)
	{
		ft_printf("0[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		data->state = TO_THINK;
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
		if (!(size_t)((t_philo*)philo->data)->life)
		{
			ft_printf("[%s] EST MORT\n", (char*)((t_philo*)philo->data)->name);
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
		ft_printf("1[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		//A FAIRE:Prend une baguette qui peut etre prise par un philosophe qui veut manger
	}
	else
	{
		ft_printf("\033[0;31mWAITING ... RET: [%d] !\033[0;m\n", ret);
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
//	ft_printf("un philosophe sauvage apparait : [%s]\n", (char*)((t_philo*)philo->data)->name);
	life = &((t_philo*)philo->data)->life;
	while ((size_t)((t_philo*)philo->data)->life)
	{
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
		{
			ft_printf("0[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			data->state = TO_REST;
			/**///

	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + REST_T)
	{
		*life = *life - 1;
		usleep(1000000);
		ft_printf("[%s][ REPOS ]Perd une vie : [%zi]\n", (char*)((t_philo*)philo->data)->name, *life);
		//if (!(size_t)((t_philo*)philo->data)->life)
		if (!*life)
		{
			ft_printf("[%s] EST MORT DE REPOS\n", (char*)((t_philo*)philo->data)->name);
				return ((void*)1);
		}
		time( (time_t*)&now_time );
	}
			/**///
		//	if (ft_waiting(&ft_rest, data, REST_T))
		//		return ((void*)1);
			//usleep(1000000 * REST_T);
			ft_printf("1[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			//PASSE EN REPOS
		}
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
	}
//	}
	return ((void*)0);
}

void	ft_create_thread(t_philo_heart **philo_heart, char *str)
{
	pthread_t		thread;
	t_philo_heart	*new_philo_heart;
	t_philo			*philo;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	philo = ft_memalloc(sizeof(t_philo));
	ft_strcpy(philo->name, str);
	philo->state = TO_REST;
	philo->life = MAX_LIFE;
	new_philo_heart->type = PHILO;
	new_philo_heart->data = philo;
	static int i = 1;
	new_philo_heart->n = i;
	ft_printf("NAME: [%s], NUMBER: [%d]\n", philo->name, i);
	while (1)
	{
		if ((*philo_heart)->type == WAND && (*philo_heart)->prev->type == WAND)
		{
			new_philo_heart->next = *philo_heart;
			new_philo_heart->prev = (*philo_heart)->prev;
			(*philo_heart)->prev->next = new_philo_heart;
			(*philo_heart)->prev = new_philo_heart;
			break ;
		}
		*philo_heart = (*philo_heart)->next;
	}
	i++;
	pthread_create (&thread, NULL, ft_philo, new_philo_heart);
	philo->thread = thread;
}

void	ft_create_wand(t_philo_heart **philo_heart)
{
	t_wand			*wand;
	t_philo_heart	*new_philo_heart;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	wand = ft_memalloc(sizeof(t_wand));
	new_philo_heart->type = WAND;
	wand->wand_state = FREE;
//	wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	//ft_bzero(&wand->mutex, sizeof(pthread_mutex_t));
	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	//wand->mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;//VERIF_ERROR
	//ft_printf("PTHREAD_MUTEX_INITIALIZER: [%d], PTHREAD_ERRORCHECK_MUTEX_INITIALIZER\n", (int)PTHREAD_MUTEX_INITIALIZER, (int)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER);
	new_philo_heart->data = wand;
	static int	i = 0;
	new_philo_heart->n = i;
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
	}
	i++;
}

void	ft_waiting_to_twerk(void)
{
	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	//ft_printf("TIME: [%zi]\n", begin_time);
	while (now_time < begin_time + TIMEOUT)
	{
		usleep(1000000);
		time( (time_t*)&now_time );
	}
	ft_printf("Now, it is time... To DAAAAAAAANCE ! ! !\n");
}

int main (void)
{
	t_philo_heart	*philo_heart;
	int				count;
	int				count2;
	char			**philo_name;
	t_philo			philo;

	ft_init_philos();
	/*
	philo_name = ft_get_philo_name();
	count = -1;
	count2 = -1;
	philo_heart = NULL;
	while (++count < NB_PHILO)
		ft_create_wand(&philo_heart);
	while (--count >= 0)
	{
		//ft_printf("[%d]\n", philo_heart->n);
		ft_create_thread(&philo_heart, philo_name[count]);
		//philo_heart = philo_heart->next;
	}*/
	/*ft_printf("COUNT: [%d]\n", count);
	count2 = -1;
	while (++count2 < NB_PHILO*2)
	{
		ft_printf("[%d] [%s]\n", philo_heart->n, philo_heart->type == PHILO ? "PHILO" : "WAND");
		philo_heart = philo_heart->next;
	}*/
	/*
	while (++count < NB_PHILO * 2)
	{
		
		if (philo_heart->type == PHILO)
		pthread_join (((t_philo*)philo_heart->data)->thread, NULL);
		philo_heart = philo_heart->next;
	}
	ft_waiting_to_twerk();*/
	return 0;
}
