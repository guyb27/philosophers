#include "../include/hello.h"

t_philo_location	*ft_get_philo_locate(int wand_number, int x, int y)
{
	(void)y;//A VOIR !
	t_philo_location *locate;

	locate = ft_memalloc(sizeof(t_philo_location));
	if (wand_number == 0)
	{
		locate->x_capsule = 2;
		//locate->x_capsule = 2 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.5) - 10;
	}
	else if (wand_number == 6)
	{
		locate->x_capsule = 9;
		//locate->x_capsule = 9 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.25) - 10;
	}
	else if (wand_number == 1)
	{
		locate->x_capsule = 9;
		//locate->x_capsule = 9 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.75) - 10;
	}
	else if (wand_number == 5)
	{
		locate->x_capsule = 16;
		//locate->x_capsule = 16 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.25) - 10;
	}
	else if (wand_number == 2)
	{
		locate->x_capsule = 16;
		//locate->x_capsule = 16 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.75) - 10;
	}
	else if (wand_number == 4)
	{
		locate->x_capsule = 23;
		//locate->x_capsule = 23 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.30) - 10;
	}
	else if (wand_number == 3)
	{
		locate->x_capsule = 23;
		//locate->x_capsule = 23 + (y - 30 >= 8 ? (y - 30) / 8 : 0);
		locate->y_capsule = (int)(x * 0.70) - 10;
	}
	locate->init = false;
	return (locate);
}
