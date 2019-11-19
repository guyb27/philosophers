/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 16:36:41 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:58:54 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char		*pf_strsub(const char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	str = NULL;
	i = -1;
	if (!s)
		return (NULL);
	start--;
	if (!(str = pf_strnew(len)))
		return (NULL);
	while (s[++start] && ++i < (int)len)
		str[i] = s[start];
	return (str);
}
