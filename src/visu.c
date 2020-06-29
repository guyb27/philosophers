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

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#define WIN_TITLE   "Philosophers"
#define WIN_WIDTH   800
#define WIN_HEIGHT  600

sfRenderWindow	*g_window;

sfColor	gui_get_color(int gui_color)
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

int		gui_init(void)
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

int		gui_exit(void)
{
	sfRenderWindow_destroy(g_window);
	return (1);
}

void	gui_print_str(float x, float y, int size, char *str)
{
	sfFont		*font;
	sfText		*text;
	sfVector2f	pos;

	font = sfFont_createFromFile("arial.ttf");
	if (!font)
	{
		printf("error: failed to create font");
		return ;
	}
	text = sfText_create();
	sfText_setString(text, str);
	sfText_setFont(text, font);
	sfText_setCharacterSize(text, size);
	pos.x = x;
	pos.y = y;
	sfText_setPosition(text, pos);
	sfRenderWindow_drawText(g_window, text, NULL);
	sfText_destroy(text);
	sfFont_destroy(font);
}

void	gui_print_rect(sfVector2f pos, sfVector2f size, sfColor color)
{
	sfRectangleShape	*rect;

	rect = sfRectangleShape_create();
	sfRectangleShape_setPosition(rect, pos);
	sfRectangleShape_setFillColor(rect, color);
	sfRectangleShape_setSize(rect, size);
	sfRectangleShape_setOutlineColor(rect, color);
	sfRenderWindow_drawRectangleShape(g_window, rect, NULL);
	sfRectangleShape_destroy(rect);
}

void	gui_print_picture(sfVector2f pos, sfVector2f scale, char *image_path)
{
	sfTexture	*texture;
	sfSprite	*sprite;

	texture = sfTexture_createFromFile(image_path, NULL);
	if (!texture)
		return ;
	sprite = sfSprite_create();
	sfSprite_setPosition(sprite, pos);
	sfSprite_scale(sprite, scale);
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfRenderWindow_drawSprite(g_window, sprite, NULL);
	sfSprite_destroy(sprite);
	sfTexture_destroy(texture);
}

void	gui_print_loadbar(sfVector2f pos, sfVector2f size, int percent)
{
	gui_print_rect(pos, size, gui_get_color(gc_background));
	gui_print_rect(pos, (sfVector2f){size.x * percent / 100, size.y}, sfRed);
}

void	gui_print_free_chopstick(t_wand *wand)
{
	if (wand->wand_state == FREE)
	{
		gui_print_picture((sfVector2f){wand->locate->y_window * 10 + 100,
						wand->locate->x_window * 20 - 15},
						(sfVector2f){0.5, 0.5},
						"images/chopstick.png");
	}
}

sfColor	gui_get_philo_color(t_philo *philo)
{
	if (philo->state == TO_REST)
		return (gui_get_color(gc_grey));
	else if (philo->state == TO_EAT)
		return (gui_get_color(gc_green));
	if (philo->life == 0)
		return (gui_get_color(gc_red));
	return (gui_get_color(gc_blue));
}

void	gui_print_philo(t_philo *philo, t_philo_heart *philo_heart)
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

void	gui_update_display(t_philo_heart *list)
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

void	gui_time_to_dance(char *s, clock_t last_frame_time, sfEvent event)
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

void		gui_end_game(t_philo_mother *mother)
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

void		gui_main_loop(t_philo_mother *mother, int timeout)
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
