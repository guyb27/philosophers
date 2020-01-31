#include "../include/hello.h"

int		ft_get_err_define_size(void)
{
	if (MAX_LIFE < 0 || EAT_T < 0 || REST_T < 0 || THINK_T < 0 || TIMEOUT < 0 ||
		NB_PHILO < 2)
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
	//VERIFIER SI IL Y A ASSEZ DE PLACE DANS LE TERMINAL POUR ACCEUILLIR TOUT LES PHILOS,
	//Ou p-e qu on peut juste ecrire ce qui se passe au milieu avec ta WINDOW*,
	//mais avec un fond rouge Damien, non ? Comme ca on gere l erreur proprement
	if (str)
	{
		ft_dprintf(2, "%s", str);
		free(str);
		return (1);
	}
	return (0);
}
