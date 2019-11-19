
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

#define handle_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info {    /* Used as argument to thread_start() */
	pthread_t thread_id;        /* ID returned by pthread_create() */
	int       thread_num;       /* Application-defined thread # */
	char     *argv_string;      /* From command-line argument */
};

#define MAX_LIFE 100
#define EAT_T 100
#define REST_T 100
#define THINK_T 100
#define TIMEOUT 100

typedef enum		e_state
{
	REST,
	EAT,
	THINK
}					t_state;

typedef struct		s_philos
{
	t_state			state;
	int				left_spoon;
	int				right_spoon;
	int				index_lst;
	struct s_philo	*next;
	struct s_philo	*prev;
	//liste doublement chainee rotative
}					t_philos;

void Hello(void);

#endif
