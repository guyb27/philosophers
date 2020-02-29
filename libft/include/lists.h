/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:48:11 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:48:11 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
