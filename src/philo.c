/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:49:27 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static char		*ft_store_philo_name(void)
{
	char		*ret;

	ft_sprintf(&ret, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s",
"Platon", "Aristote", "Heraclite", "Epictete", "Marc-Aurele", "Seneque",
"Socrate", "Descartes", "Diderot", "Fichte", "Nietzsche", "Marx", "Montaigne",
					"Montesquieu", "Rousseau", "Voltaire", "Freud", "Weber");
	return (ret);
}

char			*ft_get_name(enum e_handle_static_function h)
{
	static int	already_taken[NB_PHILO] = {0};
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

static void		ft_philo_mid(t_philo_heart **philo, void *arg)
{
	char		*str;

	while ((size_t)((t_philo*)(*philo)->data)->life &&
										(*(t_philo_mother**)arg)->all_in_life)
	{
		if ((enum e_philo_state)((t_philo*)(*philo)->data)->state == TO_EAT)
			ft_rest(philo, (t_philo**)&(*philo)->data, arg);
		else if (ft_eat_or_think(philo, (t_philo**)&(*philo)->data, arg))
		{
			//usleep(SEC);
			((t_philo*)(*philo)->data)->life =
										((t_philo*)(*philo)->data)->life - 1;
			ft_sprintf(&str, "%d", ((t_philo*)(*philo)->data)->life);
			pthread_mutex_lock(&g_gmutex);
			ft_actualize(((t_philo*)(*philo)->data)->capsule, str,
																X_LIFE, Y_LIFE);
			if (((t_philo*)(*philo)->data)->life <= 0)
				ft_sprintf(&(*(t_philo_mother**)arg)->result, "%s%s est mort\n",
			(*(t_philo_mother**)arg)->result, ((t_philo*)(*philo)->data)->name);
			pthread_mutex_unlock(&g_gmutex);
			ft_strdel(&str);
		}

	//sleep(20);
	}
}

void			*ft_philo(void *arg)
{
	t_philo_heart	*philo;

	philo = (*(t_philo_mother**)arg)->heart;
	pthread_mutex_lock(&g_gmutex);
	while ((philo->type == PHILO && ((t_philo*)philo->data)->name) ||
															philo->type == WAND)
		philo = philo->next;
	((t_philo*)(philo)->data)->name = ft_get_name(GET_INFOS);
	pthread_mutex_unlock(&g_gmutex);
	((t_philo*)(philo)->data)->state = TO_REST;
	((t_philo*)(philo)->data)->life = ft_handle_define(GET_INFOS, LIFE, 0);
	((t_philo*)philo->data)->capsule =
								ft_create_philo_window(philo->data, arg, true);
	//sleep(20);
	ft_philo_mid(&philo, arg);
	return (__DARWIN_NULL);
}
