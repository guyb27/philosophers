#include "hello.h"

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

int		ft_can_you_do_eat(t_wand *left, t_wand *right)
{
	int		ret;

	ret = pthread_mutex_trylock(&left->mutex);
	ret += pthread_mutex_trylock(&right->mutex);
	return (ret ? 0 : 1);
}

void	ft_rest(t_philo *philo)
{
	philo->life--;
	ft_printf("REPOS [%s]:[%zi]PV--\n", philo->name, philo->life);
}

void	ft_think(t_philo *philo)
{
	philo->life--;
	ft_printf("THINK [%s]:[%zi]PV--\n", philo->name, philo->life);
}

int		ft_waiting(void (*function)(t_philo *philo), t_philo *data)
{
	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	while (now_time < begin_time + TIMEOUT)
	{
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
	if (ft_can_you_do_eat(philo->prev->data, philo->next->data))
	{
		ft_printf("\033[0;32m0[%s] mange\033[0;m\n", (char*)((t_philo*)philo->data)->name);
		data->state = TO_EAT;
		data->life = MAX_LIFE;
		usleep(1000000 * EAT_T);
		pthread_mutex_unlock(&((t_wand*)philo->prev->data)->mutex);
		pthread_mutex_unlock(&((t_wand*)philo->next->data)->mutex);
		ft_printf("\033[0;32m1[%s] mange 100% LIFE\033[0;m\n", (char*)((t_philo*)philo->data)->name);
	}
	else
	{
		ft_printf("0[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		data->state = TO_THINK;
		if (ft_waiting(&ft_think, data))
			return (1);
		usleep(1000000 * THINK_T);
		ft_printf("1[%s] pense\n", (char*)((t_philo*)philo->data)->name);
		//A FAIRE:Prend une baguette qui peut etre prise par un philosophe qui veut manger
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo_heart	*philo;
	pthread_cond_t	condition;
	pthread_mutex_t	mutex;
	t_philo			*data;

	philo = (t_philo_heart*)arg;
	data = philo->data;
	ft_printf("un philosophe sauvage apparait : [%s]\n", (char*)((t_philo*)philo->data)->name);
	while ((size_t)((t_philo*)philo->data)->life)
	{
		if ((e_philo_state)((t_philo*)philo->data)->state == TO_REST)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_EAT)
		{
			ft_printf("0[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			data->state = TO_REST;
			if (ft_waiting(&ft_rest, data))
				return ((void*)1);
			//usleep(1000000 * REST_T);
			ft_printf("1[%s] se repose\n", (char*)((t_philo*)philo->data)->name);
			//PASSE EN REPOS
		}
		else if ((e_philo_state)((t_philo*)philo->data)->state == TO_THINK)
			//PEUT SOIT MANGER SOIT REFLECHIR, MAIS MANGER EST UNE PRIORITE
			ft_eat_or_think(philo, data);
	}
	return ((void*)0);
}

void	ft_add_to_philo_heart(t_philo_heart **philo_heart, t_philo_heart *new)
{
	if (!*philo_heart)
	{
		*philo_heart = new;
		new->prev = new->next;
		new->next->next = new;
	}
	else
	{
		new->next->next = *philo_heart;
		new->prev = (*philo_heart)->prev;
		(*philo_heart)->prev->next = new;
		(*philo_heart)->prev = new->next;
	}
}

void	ft_create_thread(t_philo_heart **philo_heart, char *str)
{
	pthread_t		thread;
	t_philo_heart	*new_philo_heart;
	t_wand			*wand;
	t_philo			*philo;

	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	wand = ft_memalloc(sizeof(t_wand));
	new_philo_heart->type = WAND;
	wand->wand_state = MID;
	wand->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
//	wand->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;//RAPIDE
	wand->mutex = (pthread_mutex_t)PTHREAD_ERRORCHECK_MUTEX_INITIALIZER;//VERIF_ERROR
	//	pthread_mutex_init(&wand->mutex, NULL);
	new_philo_heart->data = wand;
	new_philo_heart->next = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->next->prev = new_philo_heart;
	philo = ft_memalloc(sizeof(t_philo));
	ft_strcpy(philo->name, str);
	philo->state = TO_REST;
	philo->life = MAX_LIFE;
	new_philo_heart->next->type = PHILO;
	new_philo_heart->next->data = philo;
	pthread_create (&thread, NULL, ft_philo, new_philo_heart->next);
	philo->thread = thread;
	ft_add_to_philo_heart(philo_heart, new_philo_heart);
}

void	ft_waiting_to_twerk(void)
{
	size_t			begin_time;
	size_t			now_time;

	time( (time_t*)&begin_time );
	now_time = begin_time;
	ft_printf("TIME: [%zi]\n", begin_time);
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
	char			**philo_name;
	t_philo			philo;

//	ft_philo_sdl();
	philo_name = ft_get_philo_name();
	count = -1;
	philo_heart = NULL;
	while (++count < NB_PHILO)
	{
		ft_create_thread(&philo_heart, philo_name[count]);
	}
	count *= 2;
	while (--count >= 0)
	{
		/*
		if (philo_heart->type == PHILO)
		pthread_join (((t_philo*)philo_heart->data)->thread, NULL);
		philo_heart = philo_heart->next;
		*/
	}
	ft_waiting_to_twerk();
	return 0;
}
