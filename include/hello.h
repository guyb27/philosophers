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

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAX_LIFE 50
#define EAT_T 6
#define REST_T 4
#define THINK_T 3
#define TIMEOUT 300

#define NB_PHILO 7

#define X_LIFE 1
#define Y_LIFE 13
#define X_STATE 2
#define Y_STATE 7
#define X_TIME 3
#define Y_TIME 6
#define X_TIMEOUT 4
#define Y_TIMEOUT 11

pthread_mutex_t g_mut;

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

typedef struct			s_wand_location
{
	int					x_window;
	int					y_window;
	int					y_before;
	int					y_mid;
	int					y_after;
	int					number;
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
}						t_philo_location;

typedef struct			s_philo
{
	char				name[25];
	size_t				life;
	size_t				time;
	e_philo_state		state;
	t_philo_location	*locate;
	pthread_t			thread;
	WINDOW				*capsule;
}						t_philo;

typedef struct				s_philo_heart
{
	void					*data;
	e_type_philo_struct		type;
	struct s_philo_heart	*next;
	struct s_philo_heart	*prev;
}							t_philo_heart;

//void Hello(void);

void ft_init_curses(void);
void ft_actualize(WINDOW *capsule, char *data, int x, int y);
WINDOW *ft_create_philo_window(t_philo *philo);
void	ft_print_wand(t_philo_heart **philo_heart);
void	ft_actualize_wand(t_philo_heart **heart, e_wand_state new_state);
void	ft_eat_begin_actualize(t_philo_heart **philo);
void	ft_eat_end_actualize(t_philo_heart **philo);
void	ft_think_begin_actualize(t_philo_heart **philo, int wand);

#endif
