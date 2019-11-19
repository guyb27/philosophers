/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strnjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 17:03:03 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 17:03:07 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		i2;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		str = pf_strdup(s1);
		return (str);
	}
	if (!(str = pf_memalloc(pf_strlen(s1) + n + 1)))
		return (NULL);
	i = -1;
	i2 = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (i2 < n)
		str[i++] = s2[i2++];
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
