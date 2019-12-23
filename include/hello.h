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
#include <SDL2/SDL.h>
#include <stdbool.h>

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAX_LIFE 100
#define EAT_T 5
#define REST_T 10
#define THINK_T 10
#define TIMEOUT 10

#define NB_PHILO 7

typedef enum	s_type_philo_struct
{
	PHILO,
	WAND
}				e_type_philo_struct;

typedef enum	s_wand_state
{
	MID,
	LEFT,
	RIGHT
}				e_wand_state;

typedef struct			s_wand
{
	e_wand_state		wand_state;
	pthread_mutex_t		mutex;
	pthread_cond_t		condition;
}						t_wand;

typedef enum	s_philo_state
{
	TO_REST = 0,
	TO_EAT = 1,
	TO_THINK = 2
}				e_philo_state;

typedef struct			s_philo
{
	char				name[25];
	size_t				life;
	size_t				time;
	e_philo_state		state;
	pthread_t			thread;
}						t_philo;

typedef struct				s_philo_heart
{
	void					*data;
	e_type_philo_struct		type;
	struct s_philo_heart	*next;
	struct s_philo_heart	*prev;
}							t_philo_heart;

typedef struct 				s_philo_gui
{
	SDL_Window		*sdl_window;
	SDL_Surface		*sdl_screen_surface;
	SDL_Surface 	*sdl_hello_world;
	SDL_Window		*window;
	SDL_Surface 	*screen_surface;
}							t_philo_gui;

void Hello(void);



/*
 *	gui.c
 */

int 	ft_philo_sdl(void);
bool 	ft_philo_sdl_error(const char *info, const char *err);

/*
 *	gui_utils.c
 */

bool    ft_philo_sdl_init(t_philo_gui *philo_gui);
bool    ft_philo_sdl_load_media(t_philo_gui *philo_gui);
void    ft_philo_sdl_close(t_philo_gui *philo_gui);

#endif
