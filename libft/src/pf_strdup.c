/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 15:49:48 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:41:34 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char*)malloc(sizeof(*str) * (pf_strlen(s1) + 1));
	if (str == NULL)
		return (NULL);
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (i < pf_strlen(s1) + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
