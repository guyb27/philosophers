/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarnay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/00 00:00:00 by gbarnay           #+#    #+#             */
/*   Updated: 2020/05/01 01:01:01 by gbarnay          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

extern sfRenderWindow	*g_window;

void			gui_print_free_chopstick(t_wand *wand)
{
	if (wand->wand_state == FREE)
	{
		gui_print_picture((sfVector2f){wand->locate->y_window * 10 + 100,
						wand->locate->x_window * 20 - 15},
						(sfVector2f){0.5, 0.5},
						"images/chopstick.png");
	}
}

static sfColor	gui_get_philo_color(t_philo *philo)
{
	if (philo->state == TO_REST)
		return (gui_get_color(gc_grey));
	else if (philo->state == TO_EAT)
		return (gui_get_color(gc_green));
	if (philo->life == 0)
		return (gui_get_color(gc_red));
	return (gui_get_color(gc_blue));
}

void			gui_print_philo(t_philo *philo, t_philo_heart *philo_heart)
{
	int		x;
	int		y;
	sfColor	color;
	char	*img;

	x = philo->locate->y_capsule * 10 - 20;
	y = philo->locate->x_capsule * 20 - 15;
	color = gui_get_philo_color(philo);
	gui_print_rect((sfVector2f){x - 20, y}, (sfVector2f){200, 120}, color);
	gui_print_str(x, y, 20, philo->name);
	img = NULL;
	ft_sprintf(&img, "images/%s.png", philo->name);
	gui_print_picture((sfVector2f){x, y + 25}, (sfVector2f){0.5, 0.5}, img);
	free(img);
	gui_print_loadbar((sfVector2f){x + 90, y + 30}, (sfVector2f){80, 10},
					philo->life * 100 / ft_handle_define(GET_INFOS, LIFE, 0));
	if (philo->state == TO_EAT)
		gui_print_picture((sfVector2f){x + 100, y + 55}, (sfVector2f){0.5, 0.5},
			"images/chopsticks.png");
	else if (((t_wand*)philo_heart->prev->data)->wand_state == THINK_RIGHT ||
			((t_wand*)philo_heart->next->data)->wand_state == THINK_LEFT)
		gui_print_picture((sfVector2f){x + 100, y + 55}, (sfVector2f){0.5, 0.5},
			"images/chopstick.png");
}

void			gui_time_to_dance(char *s, clock_t last_frame_time,
																sfEvent event)
{
	while (sfRenderWindow_isOpen(g_window))
	{
		while (sfRenderWindow_pollEvent(g_window, &event))
			if (event.type == sfEvtClosed || event.type == sfEvtKeyPressed)
				sfRenderWindow_close(g_window);
		if (clock() - last_frame_time <= CLOCKS_PER_SEC / 25)
			continue;
		gui_print_rect((sfVector2f){WIN_WIDTH / 2 - 120,
				WIN_HEIGHT / 2 - 40},
				(sfVector2f){240, 100},
				(sfColor){rand() % 255, rand() % 255, rand() % 255, 255});
		ft_strcpy(s, "Now, it is time... \nTo DAAAAAAAANCE ! ! !\0");
		gui_print_str(WIN_WIDTH / 2 - (ft_strlen(s) / 4 * 12),
					WIN_HEIGHT / 2, 20, s);
		sfRenderWindow_display(g_window);
		last_frame_time = clock();
	}
}
