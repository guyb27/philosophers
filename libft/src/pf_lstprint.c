/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstprint.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/09/29 21:35:10 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:29:57 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lists.h"

static void		pf_lstjoin(t_printf *lst2, t_printf **lst)
{
	int			i;
	int			j;
	char		*s;

	s = pf_memalloc(sizeof((*lst)->str) * ((*lst)->size + lst2->size + 1));
	i = 0;
	j = 0;
	while (i < (*lst)->size)
	{
		s[i] = (*lst)->str[i];
		i++;
	}
	while (j < lst2->size)
		s[i++] = lst2->str[j++];
	s[i] = '\0';
	(*lst)->size = (*lst)->size + lst2->size;
	free((*lst)->str);
	(*lst)->str = s;
}

static t_printf	*pf_lstjoin_free(t_printf *lst)
{
	t_printf	*tmp;

	while (lst->next)
	{
		tmp = lst->next;
		pf_lstjoin(tmp, &lst);
		lst->next = tmp->next ? tmp->next : NULL;
		free(tmp->str);
		free(tmp);
	}
	return (lst);
}

int				pf_lstfprint(void **str, t_printf *lst)
{
	t_printf	*tmp;
	int			fd;

	tmp = NULL;
	if (access((char*)*str, W_OK))
	{
		if ((fd = open((char*)*str,
			O_CREAT | O_APPEND | O_WRONLY, 0770)))
		{
			tmp = pf_lstjoin_free(lst);
			write(fd, tmp->str, tmp->size);
			free(tmp->str);
		}
		else
			lst->size = 0;
	}
	else
		lst->size = 0;
	return (tmp ? tmp->size : 0);
}

int				pf_lstsprint(void **str, t_printf *lst)
{
	t_printf	*tmp;

	tmp = lst;
	tmp = pf_lstjoin_free(lst);
	*str = tmp->str;
	return (tmp->size);
}

int				pf_lstprint(void **fd, t_printf *lst)
{
	t_printf	*tmp;

	tmp = pf_lstjoin_free(lst);
	write(*((int*)fd[0]), tmp->str, tmp->size);
	free(tmp->str);
	return (tmp->size);
}
