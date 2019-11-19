/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lists.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 18:23:59 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/18 12:07:15 by gmadec      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H
# include "ft_printf.h"

typedef struct		s_printf
{
	char			*str;
	int				size;
	struct s_printf	*next;
}					t_printf;

void				pf_lstaddend(t_printf **alst, t_printf *nxt);
t_printf			*pf_lstnew(char *str, size_t len);
int					pf_lstprint(void **fd, t_printf *lst);
int					pf_lstsprint(void **fd, t_printf *lst);
int					pf_lstfprint(void **fd, t_printf *lst);

#endif
