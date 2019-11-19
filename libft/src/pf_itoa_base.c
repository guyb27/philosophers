/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_itoa_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 16:14:00 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:36:33 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

static uintmax_t	pf_pow(uintmax_t nb, int pow)
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

static int			pf_size_i(uintmax_t n, uintmax_t base)
{
	int		i;

	i = 1;
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char			pf_nbrbase(uintmax_t n, int i, int base, int maj)
{
	int		nbr;

	nbr = (uintmax_t)ABS((n / pf_pow(base, i)));
	if (nbr < 10)
		return (nbr + '0');
	else
	{
		if (maj)
			return (nbr + 'A' - 10);
		else
			return (nbr + 'a' - 10);
	}
}

char				*pf_itoa_base_unsigned(uintmax_t n, int base, int maj)
{
	char	*str;
	int		i;
	int		a;

	i = pf_size_i(n, base);
	if (!(str = (char*)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	a = 0;
	while (i > 0)
	{
		i--;
		str[a] = pf_nbrbase(n, i, base, maj);
		n = n % pf_pow(base, i);
		a++;
	}
	str[a] = 0;
	return (str);
}
