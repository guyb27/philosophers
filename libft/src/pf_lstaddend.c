/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
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
