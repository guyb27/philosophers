/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/11/24 16:56:49 by qcharpen     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/17 18:35:29 by qcharpen    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lists.h"

void	pf_lstaddend(t_printf **alst, t_printf *nxt)
{
	t_printf	*curr;

	if (!*alst)
		*alst = nxt;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nxt;
	}
}
