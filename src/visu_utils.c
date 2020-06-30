/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbarnay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/00 00:00:00 by gbarnay           #+#    #+#             */
/*   Updated: 2020/05/01 01:01:01 by gbarnay          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hello.h"

extern sfRenderWindow	*g_window;

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
