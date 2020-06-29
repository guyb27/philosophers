/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 04:41:51 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

int		ft_get_err_define_size(void)
{
	if (MAX_LIFE < 1 || EAT_T < 1 || REST_T < 1 || THINK_T < 1 || TIMEOUT < 0 ||
		NB_PHILO != 7)
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
