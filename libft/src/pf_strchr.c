/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 15:45:29 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 15:45:31 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strchr(const char *s, int c)
{
	size_t			i;

	i = 0;
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char*)&s[i]);
	else
		return (NULL);
}
