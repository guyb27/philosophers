/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:44:15 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 12:44:15 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdelone(t_list **alst, void (*del)())
{
	del((*alst)->content, (*alst)->content_size);
	ft_memdel((void *)alst);
}
