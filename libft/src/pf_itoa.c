/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 13:24:43 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft_printf.h"

static long long int	pf_pow(long long int nb, int pow)
{
	if (nb == 0)
		return (0);
	if (pow == 0)
		return (1);
	else if (pow > 0)
		return (nb * pf_pow(nb, pow - 1));
	else
		return (1 / pf_pow(nb, -pow));
}

static int				pf_size_i(long long int n)
{
	int		i;

	i = 1;
	if (n < 0)
		i++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char					*pf_itoa(long long int n)
{
	char				*str;
	int					i;
	int					a;
	int					tmp;

	i = pf_size_i(n);
	if (!(str = (char*)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	a = 0;
	if (n < 0)
	{
		str[a++] = '-';
		i--;
	}
	while (i > 0)
	{
		i--;
		tmp = (n / pf_pow(10, i)) > 0 ? (n / pf_pow(10, i)) :
														-(n / pf_pow(10, i));
		str[a] = tmp + '0';
		n = n % (long long int)pf_pow(10, i);
		a++;
	}
	str[a] = 0;
	return (str);
}
