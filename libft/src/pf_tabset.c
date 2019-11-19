/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_tabset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 16:35:17 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:35:19 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

void	*pf_tabset(size_t len)
{
	int		*tab;

	tab = pf_memalloc(sizeof(*tab) * len);
	while (len > 0)
	{
		len--;
		tab[len] = 0;
	}
	return (tab);
}
