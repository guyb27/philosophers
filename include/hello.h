/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmadec <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:27:41 by gmadec            #+#    #+#             */
/*   Updated: 2020/03/04 03:56:10 by gmadec           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELLO_H
# define HELLO_H

# define _DEFAULT_SOURCE

# include "../libft/include/libft.h"

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>
# include <curses.h>
# include <signal.h>

# define MAX_LIFE 12
# define EAT_T 2
# define REST_T 2
# define THINK_T 4
# define TIMEOUT 30
# define NB_PHILO 7

# define X_LIFE 1
# define Y_LIFE 13
# define X_STATE 2
# define Y_STATE 7
# define X_TIME 3
# define Y_TIME 6
# define X_TIMEOUT 4
# define Y_TIMEOUT 11

# define SEC 1000000
# define RESULT "philo_game"

# define ENTER 10
# define ESCAPE 27
# define SPACE 32

pthread_mutex_t					g_gmutex;
int								g_gmode;

enum							e_gmode
{
	NOT_INIT,
	NOTHING_WINDOW,
	ALL_WINDOWS
};

enum							e_ret_status
{
	NOTHING,
	LEFT,
	RIGHT,
	ALL
};

enum							e_type_philo_struct
{
	PHILO,
	WAND
};

enum							e_wand_state
{
	FREE,
	THINK_LEFT,
	THINK_RIGHT,
	EAT_LEFT,
	EAT_RIGHT
};

enum							e_handle_static_function
{
	INIT,
	ACTUALIZE,
	GET_INFOS,
	Y_ACTUALIZE,
	X_ACTUALIZE,
	ACTUALIZE_SCREEN,
	DEL
};

enum							e_define_type
{
	LIFE,
	EAT,
	REST,
	THINK,
	TIME,
	NBPHILO
};

enum							e_gui_colors
{
	gc_background,
	gc_green,
	gc_blue,
	gc_grey,
	gc_red
};

typedef struct					s_wand_location
{
	int							x_window;
	int							y_window;
	int							y_before;
	int							y_mid;
	int							y_after;
	int							number;
	bool						init;
}								t_wand_location;

typedef struct					s_wand
{
	enum e_wand_state			wand_state;
	pthread_mutex_t				mutex;
	pthread_cond_t				condition;
	t_wand_location				*locate;
	WINDOW						*capsule;
	int							number;
}								t_wand;

enum							e_philo_state
{
	TO_REST = 0,
	TO_EAT = 1,
	TO_THINK = 2
};

typedef struct					s_philo_location
{
	int							x_capsule;
	int							y_capsule;
	bool						init;
}								t_philo_location;

typedef struct					s_philo
{
	char						*name;
	size_t						life;
	size_t						time;
	enum e_philo_state			state;
	t_philo_location			*locate;
	WINDOW						*capsule;
}								t_philo;

typedef struct					s_philo_heart
{
	void						*data;
	enum e_type_philo_struct	type;
	struct s_philo_heart		*next;
	struct s_philo_heart		*prev;
}								t_philo_heart;

typedef struct					s_screen_size
{
	int							x;
	int							y;
}								t_screen_size;

typedef struct					s_philo_mother
{
	t_philo_heart				*heart;
	WINDOW						*win;
	WINDOW						*win_game_var;
	WINDOW						*state_game;
	t_screen_size				ss;
	char						*result;
	bool						all_in_life;
}								t_philo_mother;

typedef struct					s_main_menu
{
	WINDOW						**items;
	int							y_pos;
	t_screen_size				ss;
}								t_main_menu;

void							ft_init_curses(void);
void							ft_actualize(WINDOW *capsule, char *data, int x,
																		int y);
void							ft_actualize_wand(t_philo_heart **heart,
												enum e_wand_state new_state);
WINDOW							*ft_create_philo_window(t_philo *philo,
									t_philo_mother **mother, bool mutex_lock);
int								ft_print_wand(t_philo_heart *philo_heart,
									t_philo_mother *mother, bool mutex_lock);
void							ft_print_game_var(t_philo_mother **mother,
															bool mutex_lock);
void							ft_main_loop(t_philo_mother **mother);
int								ft_get_err_define_size(void);
int								ft_catch_error(int ac, char **av);
int								ft_handle_define(
			enum e_handle_static_function h, enum e_define_type d, int value);
void							ft_menu(void);
void							ft_handle_wand_location(
t_wand_location **locate, enum e_handle_static_function h, t_screen_size ss);
void							ft_init_and_begin_game(void);
void							ft_init_and_begin_main_menu(void);
void							ft_free_philo_mother(t_philo_mother *mother);
void							*ft_handle_mother_addr(void *mother,
											enum e_handle_static_function h);
t_main_menu						*ft_handle_main_menu(
	enum e_handle_static_function h, int data1, bool lock_mutex, void *data2);
void							ft_print_define(WINDOW *win, int i);
int								ft_end_menu(int x, int y, int color);
void							ft_init_main_menu(bool lock_mutex, int data1,
															t_main_menu **menu);
int								ft_eat(t_philo **data, t_philo_heart **philo,
													t_philo_mother **mother);
int								ft_think(int ret, t_philo_heart **philo,
									t_philo **data, t_philo_mother **mother);
int								ft_rest(t_philo_heart **philo, t_philo **data,
													t_philo_mother **mother);
int								ft_eat_or_think(t_philo_heart **philo,
									t_philo **data, t_philo_mother **mother);
void							ft_init_and_begin_game(void);
void							*ft_create_mother_window(int y, int x);
void							ft_create_wand(t_philo_heart **philo_heart,
															t_screen_size ss);
void							ft_create_philo(t_philo_heart **philo_heart,
															t_screen_size ss);
void							*ft_philo(void *arg);
char							*ft_get_name(enum e_handle_static_function h);
t_philo_location				*ft_get_philo_locate(int wand_number, int x,
																		int y);
void							ft_resize(int sig);
int								ft_change_value(int value, int selected,
																WINDOW **items);
void							ft_create_main_menu(int data1,
															t_main_menu **menu);

//void							ft_end_game(char *str, t_philo_mother **mother);
/*
**	visu.c
*/
int    							gui_init(void);
void    						gui_main_loop(t_philo_mother *mother, int timeout);
int    							gui_test(void);


#endif
