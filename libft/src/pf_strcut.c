/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_strcut.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gmadec <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/17 16:33:27 by gmadec       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/17 16:33:28 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/libft_printf.h"

char	*pf_strcut(const char *s, size_t i)
{
	size_t	j;
	char	*rst;

	if (i <= 0)
		return (NULL);
	if (i > pf_strlen(s))
		i = pf_strlen(s);
	rst = (char*)pf_memalloc(sizeof(*rst) * (i + 1));
	j = 0;
	while (j < i && s[j])
	{
		rst[j] = s[j];
		j++;
	}
	rst[j] = '\0';
	return (rst);
}
