#ifndef H_GL_HELLO
#define H_GL_HELLO
# include "../libft/include/libft.h"

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <curses.h>
#include <signal.h>

#define MAX_LIFE 12
#define EAT_T 2
#define REST_T 2
#define THINK_T 2
#define TIMEOUT 2
#define NB_PHILO 7

#define X_LIFE 1
#define Y_LIFE 13
#define X_STATE 2
#define Y_STATE 7
#define X_TIME 3
#define Y_TIME 6
#define X_TIMEOUT 4
#define Y_TIMEOUT 11

#define SEC 1000000
# define RESULT "philo_game"

#define ENTER 10
#define ESCAPE 27
#define SPACE 32

pthread_mutex_t g_gmutex;
int				g_gmode;

typedef enum	s_gmode
{
	NOT_INIT,
	NOTHING_WINDOW,
	ALL_WINDOWS
}				e_gmode;

typedef enum	s_ret_status
{
	NOTHING,
	LEFT,
	RIGHT,
	ALL
}				e_ret_status;

typedef enum	s_type_philo_struct
{
	PHILO,
	WAND
}				e_type_philo_struct;

typedef enum	s_wand_state
{
	FREE,
	THINK_LEFT,
	THINK_RIGHT,
	EAT_LEFT,
	EAT_RIGHT
}				e_wand_state;

typedef enum	s_handle_static_function
{
	INIT,
	ACTUALIZE,
	GET_INFOS,
	Y_ACTUALIZE,
	X_ACTUALIZE,
	ACTUALIZE_SCREEN,
	DEL
}				e_handle_static_function;

typedef enum	s_define_type
{
	LIFE,
	EAT,
	REST,
	THINK,
	TIME,
	NBPHILO
}				e_define_type;

typedef struct			s_wand_location
{
	int					x_window;
	int					y_window;
	int					y_before;
	int					y_mid;
	int					y_after;
	int					number;
	bool				init;
}						t_wand_location;

typedef struct			s_wand
{
	e_wand_state		state;
	e_wand_state		reserve;
	pthread_mutex_t		mutex;
	pthread_cond_t		condition;
	t_wand_location		*locate;
	WINDOW				*capsule;
	int					number;
}						t_wand;

typedef enum	s_philo_state
{
	TO_REST,
	TO_EAT,
	TO_THINK
}				e_philo_state;

typedef struct			s_philo_location
{
	int					x_capsule;
	int					y_capsule;
	bool				init;
}						t_philo_location;

typedef struct			s_philo
{
	char				*name;
	size_t				life;
	size_t				time;
	e_philo_state		state;
	t_philo_location	*locate;
	WINDOW				*capsule;
}						t_philo;

typedef struct				s_philo_heart
{
	void					*data;
	e_type_philo_struct		type;
	struct s_philo_heart	*next;
	struct s_philo_heart	*prev;
}							t_philo_heart;

typedef struct				s_screen_size
{
	int						x;
	int						y;
}							t_screen_size;

typedef struct				s_philo_mother
{
	t_philo_heart	*heart;
	WINDOW			*win;
	WINDOW			*win_game_var;
	WINDOW			*state_game;
	t_screen_size	ss;
	char			*result;
	bool all_in_life;
}							t_philo_mother;

typedef struct				s_main_menu
{
	WINDOW					**items;
	int						y_pos;
	t_screen_size	ss;
}							t_main_menu;

void			ft_init_curses(void);
void			ft_actualize(WINDOW *capsule, char *data, int x, int y);
void			ft_actualize_wand(t_philo_heart **heart, e_wand_state new_state);
WINDOW			*ft_create_philo_window(t_philo *philo, t_philo_mother **mother, bool mutex_lock);
int				ft_print_wand(t_philo_heart *philo_heart, t_philo_mother *mother, bool mutex_lock);
void			ft_print_game_var(t_philo_mother **mother, bool mutex_lock);
void			ft_main_loop(t_philo_mother **mother);
int				ft_get_err_define_size(void);
int				ft_catch_error(int ac, char **av);
int				ft_handle_define(e_handle_static_function h, e_define_type d, int value);
void			ft_menu(void);
void			ft_handle_wand_location(t_wand_location **locate, e_handle_static_function h, t_screen_size ss);
void			ft_init_and_begin_game(void);
void			ft_init_and_begin_main_menu(void);
void			ft_free_philo_mother(t_philo_mother *mother);
void			*ft_handle_mother_addr(void *mother, e_handle_static_function h);
t_main_menu		*ft_handle_main_menu(e_handle_static_function h, int data1, bool lock_mutex, void *data2);
void			ft_print_define(WINDOW *win, int i);
int				ft_end_menu(int x, int y, int color);
void			ft_init_main_menu(bool lock_mutex, int data1, t_main_menu **menu);
int				ft_eat(t_philo **data, t_philo_heart **philo, t_philo_mother **mother);
int				ft_think(int ret, t_philo_heart **philo, t_philo **data, t_philo_mother **mother);
int				ft_rest(t_philo_heart **philo, t_philo **data, t_philo_mother **mother);
int				ft_eat_or_think(t_philo_heart **philo, t_philo **data, t_philo_mother **mother);
void			ft_init_and_begin_game(void);
void			*ft_create_mother_window(int y, int x);
void			ft_create_wand(t_philo_heart **philo_heart, t_screen_size ss);
void			ft_create_philo(t_philo_heart **philo_heart, t_screen_size ss);
void			*ft_philo(void *arg);
char			*ft_get_name(e_handle_static_function h);
t_philo_location	*ft_get_philo_locate(int wand_number, int x, int y);
void				ft_reserve_meal(t_philo_heart **heart);

#endif
