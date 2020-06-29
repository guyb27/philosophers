/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:20 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:20 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lists.h"

t_printf	*pf_lstnew(char *str, size_t len)
{
	t_printf	*new;

	new = (t_printf*)malloc(sizeof(*new));
	new->str = str;
	new->size = len;
	new->next = NULL;
	return (new);
}
