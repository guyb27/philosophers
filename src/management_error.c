#include "../include/hello.h"

int		ft_get_err_define_size(void)
{
	if (MAX_LIFE < 0 || EAT_T < 0 || REST_T < 0 || THINK_T < 0 || TIMEOUT < 0 ||
		NB_PHILO < 2 || NB_PHILO > 7)
		return (1);
	return (0);
}

int		ft_catch_error(int ac, char **av)
{
	char	*str;

	str = NULL;
	if (ac > 1)
		ft_sprintf(&str, "%susage: %s%s\n", RED, av[0], STOP);
	else if (ft_get_err_define_size())
		ft_sprintf(&str, "%sDefine error(s)%s\n", RED, STOP);
	if (str)
	{
		ft_dprintf(2, "%s", str);
		free(str);
		return (1);
	}
	return (0);
}
