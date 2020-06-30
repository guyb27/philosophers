/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarnay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/00 00:00:00 by gbarnay           #+#    #+#             */
/*   Updated: 2020/05/01 01:01:01 by gbarnay          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

sfRenderWindow	*g_window;

sfColor			gui_get_color(int gui_color)
{
	if (gui_color == gc_background)
		return ((sfColor){30, 30, 30, 255});
	else if (gui_color == gc_green)
		return ((sfColor){78, 201, 176, 150});
	else if (gui_color == gc_blue)
		return ((sfColor){86, 156, 214, 150});
	if (gui_color == gc_grey)
		return ((sfColor){60, 60, 60, 255});
	if (gui_color == gc_red)
		return ((sfColor){150, 60, 60, 255});
	return ((sfColor){0, 0, 0, 255});
}

static void		gui_update_display(t_philo_heart *list)
{
	t_philo_heart	*entity;

	sfRenderWindow_clear(g_window, gui_get_color(gc_background));
	entity = list;
	while (1)
	{
		if (entity->type == PHILO)
			gui_print_philo((t_philo*)entity->data, entity);
		else if (entity->type == WAND)
			gui_print_free_chopstick((t_wand*)entity->data);
		if (entity->next == list)
			break ;
		entity = entity->next;
	}
	sfRenderWindow_display(g_window);
}

static void		gui_end_game(t_philo_mother *mother)
{
	char	s[2048];
	sfEvent event;
	clock_t last_frame_time;

	last_frame_time = 1;
	if (mother->all_in_life)
	{
		mother->all_in_life = false;
		gui_time_to_dance(s, last_frame_time, event);
	}
	else
		ft_strcpy(s, "A philosopher is dead !!!\0");
	gui_print_str(WIN_WIDTH / 2 - (ft_strlen(s) / 3 * 10),
				WIN_HEIGHT / 2 - 20, 20, s);
	mother->all_in_life = false;
	usleep(SEC);
	sfRenderWindow_display(g_window);
	while (sfRenderWindow_isOpen(g_window))
	{
		while (sfRenderWindow_pollEvent(g_window, &event))
			if (event.type == sfEvtClosed || event.type == sfEvtKeyPressed)
				sfRenderWindow_close(g_window);
	}
}

int				gui_init(void)
{
	sfVideoMode mode;

	mode.width = WIN_WIDTH;
	mode.height = WIN_HEIGHT;
	mode.bitsPerPixel = 32;
	g_window = sfRenderWindow_create(mode, WIN_TITLE, sfResize | sfClose, NULL);
	if (!g_window)
	{
		printf("error: failed to create window for sfml");
		return (0);
	}
	return (1);
}

void			gui_main_loop(t_philo_mother *mother, int timeout)
{
	sfEvent	event;
	time_t	begin_time;
	clock_t	last_frame_time;

	time(&begin_time);
	last_frame_time = 1;
	while (sfRenderWindow_isOpen(g_window))
	{
		while (sfRenderWindow_pollEvent(g_window, &event))
			if (event.type == sfEvtClosed || event.type == sfEvtKeyPressed)
				sfRenderWindow_close(g_window);
		if (clock() - last_frame_time <= CLOCKS_PER_SEC / 61)
			continue ;
		pthread_mutex_lock(&g_gmutex);
		gui_update_display(mother->heart);
		pthread_mutex_unlock(&g_gmutex);
		last_frame_time = clock();
		if (time(NULL) >= begin_time + timeout || mother->all_in_life == 0)
			break ;
	}
	gui_update_display(mother->heart);
	gui_end_game(mother);
	sfRenderWindow_destroy(g_window);
}
