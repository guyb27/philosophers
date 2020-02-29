/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:41:51 by gmadec            #+#    #+#             */
/*   Updated: 2020/02/29 05:08:45 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

static void	ft_creat_menu(WINDOW ***menu, int x, int y, int color)
{
	int		i;

	i = 0;
	*menu = (WINDOW**)malloc(sizeof(WINDOW*) * 5);
	(*menu)[0] = newwin(6, 20, (y / 2) - 2, (x / 2) - 10);
	wbkgd((*menu)[0], COLOR_PAIR(color == 7 ? 6 : 5));
	box((*menu)[0], '|', '-');
	while (++i < 5)
		(*menu)[i] = subwin((*menu)[0], 1, 18, (y / 2) - (2 - i), (x / 2) -
																	(10 - 1));
	wbkgd((*menu)[1], COLOR_PAIR(color));
	wprintw((*menu)[1], "Try again");
	wprintw((*menu)[2], "Main menu");
	wprintw((*menu)[3], "Cancel");
	wprintw((*menu)[4], "Quit");
	wrefresh((*menu)[0]);
}

static int	ft_cancel(WINDOW ***menu, int ret)
{
	int		i;

	i = -1;
	while (++i < 5)
		delwin((*menu)[i]);
	wclear((*menu)[0]);
	wbkgd((*menu)[0], COLOR_PAIR(1));
	wrefresh((*menu)[0]);
	free(*menu);
	return (ret);
}

static void	ft_vertical_keys(WINDOW ***menu, int *selected, int key, int color)
{
	wbkgd((*menu)[*selected + 1], COLOR_PAIR(color == 7 ? 6 : 5));
	wnoutrefresh((*menu)[*selected + 1]);
	if (key == KEY_DOWN)
		*selected = (*selected + 1) % 4;
	else
		*selected = (*selected - 1 + 4) % 4;
	wbkgd((*menu)[*selected + 1], COLOR_PAIR(color));
	wnoutrefresh((*menu)[*selected + 1]);
	doupdate();
}

int			ft_end_menu(int x, int y, int color)
{
	WINDOW	**menu;
	int		key;
	int		selected;

	key = 0;
	selected = 0;
	ft_creat_menu(&menu, x, y, color);
	while (g_gmode == ALL_WINDOWS)
	{
		key = getch();
		if (key == ENTER || key == ESCAPE)
		{
			if (selected + 1 == 1 && !(key == ESCAPE))
				return (ft_cancel(&menu, 1));
			else if (selected + 1 == 2 && !(key == ESCAPE))
				return (ft_cancel(&menu, 2));
			else if (selected + 1 == 3 || key == ESCAPE)
				return (ft_cancel(&menu, 0));
			else if (selected + 1 == 4 && !(key == ESCAPE))
				return (ft_cancel(&menu, 3));
		}
		else if (key == KEY_DOWN || key == KEY_UP)
			ft_vertical_keys(&menu, &selected, key, color);
	}
	return (0);
}
