#include "../include/hello.h"

int		ft_print_wand(t_philo_heart *philo_heart, t_philo_mother *mother, bool mutex_lock)//Faire une fonction plus propre qui utilise ft_actualize
{
	t_wand	*wand;
	char *str = NULL;

	if (((t_philo*)philo_heart->prev->data)->name && ((t_philo*)philo_heart->next->data)->name)
	{
		if (mutex_lock)
			pthread_mutex_lock(&g_gmutex);
		((t_wand*)philo_heart->data)->capsule = subwin(mother->win, 1, 40,
		((t_wand*)philo_heart->data)->locate->x_window,
		((t_wand*)philo_heart->data)->locate->y_window);
		wbkgd(((t_wand*)philo_heart->data)->capsule, COLOR_PAIR(2));
		wand = philo_heart->data;
		wmove(wand->capsule, 0, 0);
		wclrtoeol(wand->capsule);
		ft_sprintf(&str, "%d%s:[%s], MID:[%s], %s:[%s]",
		wand->locate->number,
		((t_philo*)philo_heart->prev->data)->name,
		wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT ? "|" :
		" ",
		wand->wand_state == FREE ? "|" : " ",
		((t_philo*)philo_heart->next->data)->name,
		wand->wand_state == THINK_RIGHT || wand->wand_state == EAT_RIGHT ? "|"
		: " ");
		wand->locate->y_before =
					ft_strlen(((t_philo*)philo_heart->prev->data)->name) + 3;
		wand->locate->y_mid = wand->locate->y_before + 9;
		wand->locate->y_after = wand->locate->y_mid + 6 +
						ft_strlen(((t_philo*)philo_heart->next->data)->name);
		wand->locate->init = true;
		wprintw(wand->capsule, str);
		wrefresh(wand->capsule);
		if (mutex_lock)
			pthread_mutex_unlock(&g_gmutex);
		ft_strdel(&str);
		return (1);
	}
	return (0);
}

void		ft_actualize_wand(t_philo_heart **heart, e_wand_state new_state)
{
	t_wand	*wand;
	int		y;

	if ((*heart)->type == WAND && (*heart)->prev->type == PHILO && (*heart)->prev->type == PHILO)
	{
		wand = ((t_wand*)(*heart)->data);
		if (wand->locate->init)
		{
			y = wand->locate->y_before;
			wmove(wand->capsule, 0, y);
			wprintw(wand->capsule, " ");
			y = wand->locate->y_mid;
			wmove(wand->capsule, 0, y);
			wprintw(wand->capsule, " ");
			y = wand->locate->y_after;
			wmove(wand->capsule, 0, y);
			wprintw(wand->capsule, " ");
			wand->wand_state = new_state;
			if (wand->wand_state == THINK_LEFT || wand->wand_state == EAT_LEFT)
				y = wand->locate->y_before;
			else
				y = wand->wand_state == FREE ? wand->locate->y_mid : wand->locate->y_after;
			wmove(wand->capsule, 0, y);
			wprintw(wand->capsule, "|");
			wrefresh(wand->capsule);
		}
		else
			wand->wand_state = new_state;
	}
}
