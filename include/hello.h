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

#define MAX_LIFE 150
#define EAT_T 2
#define REST_T 3
#define THINK_T 4
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

#define ENTER 10
#define ESCAPE 27
#define SPACE 32

//bool g_all_in_life;


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
	GET_INFOS
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
	e_wand_state		wand_state;//REMPLACER PAR STATE
	pthread_mutex_t		mutex;
	pthread_cond_t		condition;
	t_wand_location		*locate;
	WINDOW				*capsule;
}						t_wand;

typedef enum	s_philo_state
{
	TO_REST = 0,
	TO_EAT = 1,
	TO_THINK = 2
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
	pthread_mutex_t mutex;
	t_screen_size	ss;
	bool all_in_life;
}							t_philo_mother;

void			ft_init_curses(void);
void			ft_actualize(WINDOW *capsule, char *data, int x, int y);
void			ft_actualize_wand(t_philo_heart **heart, e_wand_state new_state);
WINDOW			*ft_create_philo_window(t_philo *philo, t_philo_mother **mother);
int				ft_print_wand(t_philo_heart *philo_heart, t_philo_mother *mother);
size_t			ft_eat_begin_actualize(t_philo_heart **philo, t_philo_mother **mother);
void			ft_eat_end_actualize(t_philo_heart **philo, t_philo_mother **mother);
size_t			ft_think_begin_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother);
void			ft_think_end_actualize(t_philo_heart **philo, int wand, t_philo_mother **mother);
size_t			ft_rest_begin_actualize(t_philo_heart **philo, t_philo_mother **mother);
void			ft_print_game_var(t_philo_mother *mother);
void			ft_main_loop(t_philo_mother **mother);
void			ft_free_philo_heart(t_philo_heart *philo);
int				ft_get_err_define_size(void);
int				ft_catch_error(int ac, char **av);
int				ft_handle_define(e_handle_static_function h, e_define_type d, int value);
void			ft_menu(void);
void			ft_handle_wand_location(t_wand_location **locate, e_handle_static_function h, t_screen_size ss);
void			ft_init_and_begin_game(void);
void			ft_init_and_begin_main_menu(void);
void			ft_free_philo_mother(t_philo_mother *mother);
void			*ft_handle_mother_addr(void *mother, e_handle_static_function h);

#endif
