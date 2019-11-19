/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_ftoa.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 15:58:38 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:34:13 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

double					pf_next_n(double n, int ent)
{
	int		i;

	i = ABS(n / pf_pow(10, ent - 1));
	if (n > 0)
		n -= i * (pf_pow(10, ent - 1));
	else
		n += i * (pf_pow(10, ent - 1));
	return (n);
}

void					pf_end_of_ftoa(int dec, long double n, int i, char **str)
{
	while (dec > 0)
	{
		n *= 10;
		(*str)[i++] = ((int)n) + '0';
		n -= ((int)n);
		dec--;
		if (dec == 0 && ABS(n * 10) >= 5)
			str[i - 1]++;
	}
	(*str)[i++] = '\0';
}

char					*pf_ftoa(long double n, int dec)
{
	int		ent;
	char	*str;
	int		i;

	ent = 1;
	i = 0;
	while (n > pf_pow(10, ent) || n < -pf_pow(10, ent))
		ent++;
	str = pf_memalloc(sizeof(*str) * (dec + ent + 2 + (n < 0 ? 1 : 0)));
	if (n < 0)
	{
		n *= -1;
		str[i++] = '-';
	}
	while (ent > 0)
	{
		str[i++] = ABS(n / pf_pow(10, ent - 1)) + '0';
		n = pf_next_n(n, ent);
		ent--;
	}
	if (dec > 0)
		str[i++] = '.';
	pf_end_of_ftoa(dec, n, i, &str);
	return (str);
}
