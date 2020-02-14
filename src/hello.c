#include "../include/hello.h"

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	if (g_gmode == ALL_WINDOWS)
	{
		wmove(capsule, x, y);
		wclrtoeol(capsule);
		wprintw(capsule, data);
		wrefresh(capsule);
	}
}

WINDOW	*ft_create_philo_window(t_philo *philo, t_philo_mother **mother, bool mutex_lock)//PAS BESOIN DE DOUBLE ETOILE POUR MOTHER
{
	WINDOW *capsule;

	capsule = NULL;
	if (g_gmode == ALL_WINDOWS)
	{
		if (mutex_lock)
			pthread_mutex_lock(&g_gmutex);
		philo->locate->init = true;
		capsule = subwin((*mother)->win, 4, 20, philo->locate->x_capsule, philo->locate->y_capsule);
		wbkgd(capsule, COLOR_PAIR(3));
		wmove(capsule, 0, 0);
		wprintw(capsule, "NAME: ");
		wprintw(capsule, philo->name);
		wmove(capsule, 1, 0);
		wprintw(capsule, "LIFE POINTS: ");
		wprintw(capsule, "%d", philo->life);
		wmove(capsule, 2, 0);
		wprintw(capsule, "STATE: ");
		wprintw(capsule, philo->state == TO_REST ? "SE REPOSE" : philo->state == TO_EAT ? "MANGE" : philo->state == TO_THINK ? "PENSE" : "UNKNOW");
		wmove(capsule, 3, 0);
		wprintw(capsule, "TIME: ");
		wprintw(capsule, "%d", philo->time);
		wrefresh(capsule);
		if (mutex_lock)
			pthread_mutex_unlock(&g_gmutex);
	}
	return (capsule);
}
