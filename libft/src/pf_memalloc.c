/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 16:17:05 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:17:08 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

void	*pf_memalloc(size_t size)
{
	char	*str;

	if (!(str = (char*)malloc(size)))
		return (NULL);
	while (size--)
		str[size] = '\0';
	return (str);
}
