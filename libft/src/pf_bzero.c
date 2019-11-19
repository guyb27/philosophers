/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_bzero.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 17:06:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:32:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

void	pf_bzero(void *s, size_t n)
{
	while (n)
	{
		((int*)s)[n] = 0;
		n--;
	}
}
