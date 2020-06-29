/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:50:01 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static void	ft_init_and_print_wand(t_philo_heart *philo_heart)
{
	t_wand	*wand;
//	char	*str;

	wand = philo_heart->data;
	wand->locate->y_before =
		ft_strlen(((t_philo*)philo_heart->prev->data)->name) + 2;
	wand->locate->y_mid = wand->locate->y_before + 9;
	wand->locate->y_after = wand->locate->y_mid + 6 +
		ft_strlen(((t_philo*)philo_heart->next->data)->name);
	wand->locate->init = true;
/*	ft_sprintf(&str, "%s:[%s], MID:[%s], %s:[%s]",
			((t_philo*)philo_heart->prev->data)->name,
		wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT ? "|" :
		" ",
		wand->wand_state == FREE ? "|" : " ",
		((t_philo*)philo_heart->next->data)->name,
		wand->wand_state == THINK_RIGHT || wand->wand_state == EAT_RIGHT ? "|"
		: " ");*/
/*	wbkgd(((t_wand*)philo_heart->data)->capsule, COLOR_PAIR(2));
	wmove(wand->capsule, 0, 0);
	wclrtoeol(wand->capsule);
	wprintw(wand->capsule, str);
	wrefresh(wand->capsule);*/
//	ft_strdel(&str);
}

int			ft_print_wand(t_philo_heart *philo_heart, t_philo_mother *mother,
																bool mutex_lock)
{
	if (((t_philo*)philo_heart->prev->data)->name &&
			((t_philo*)philo_heart->next->data)->name && g_gmode == ALL_WINDOWS)
	{
		mutex_lock ? pthread_mutex_lock(&g_gmutex) : 0;
		((t_wand*)philo_heart->data)->capsule = subwin(mother->win, 1, 40,
			((t_wand*)philo_heart->data)->locate->x_window,
			((t_wand*)philo_heart->data)->locate->y_window);
		ft_init_and_print_wand(philo_heart);
		mutex_lock ? pthread_mutex_unlock(&g_gmutex) : 0;
		return (1);
	}
	return (0);
}

void		ft_actualize_wand(t_philo_heart **heart,
													enum e_wand_state new_state)
{
	t_wand	*wand;

	wand = ((t_wand*)(*heart)->data);
	//if ((*heart)->type == WAND && (*heart)->prev->type == PHILO &&
//(*heart)->next->type == PHILO && g_gmode == ALL_WINDOWS && wand->locate->init)
	wand->wand_state = new_state;
}
