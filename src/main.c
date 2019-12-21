#include "hello.h"

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

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
	TO_REST,
	TO_EAT,
	TO_THIK
}				e_philo_state;

typedef struct			s_philo
{
	char				name[25];
	e_philo_state		philo_state;
	pthread_t			thread;
}						t_philo;

typedef struct				s_philo_heart
{
	void					*data;
	e_type_philo_struct		type;
	char					test[100];
	struct s_philo_heart	*next;
	struct s_philo_heart	*prev;
}							t_philo_heart;

void	*ft_philo(void *arg)
{
/*	t_philo_heart	philo_heart;

	//ft_init_struct(*(t_philo_heart*)arg);
	philo_heart = *(t_philo_heart*)arg;
	ft_strcpy(philo_heart[0].test, "Bonjour les amis");
	ft_printf("%s\n", philo_heart[0].test);
	*/
	return (NULL);
}

void	ft_create_thread(t_philo_heart **philo_heart, char *str)
{
	pthread_t		thread;
	t_philo_heart	*new_philo_heart;
	t_philo_heart	*new_next_philo_heart;
	t_wand			wand;
	t_philo			philo;

	pthread_create (&thread, NULL, ft_philo, *philo_heart);
	new_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_philo_heart->type = WAND;
	wand.condition = (pthread_cond_t){0};
	ft_strcpy(philo.name, str);
	philo.thread = thread;
	new_next_philo_heart = ft_memalloc(sizeof(t_philo_heart));
	new_next_philo_heart->prev = new_philo_heart;
	new_philo_heart->next = new_next_philo_heart;
	new_next_philo_heart->data = &philo;
	//wand.condition = PTHREAD_COND_INITIALIZER;
	//wand.mutex = PTHREAD_MUTEX_INITIALIZER;
	new_philo_heart->data = &wand;
	new_next_philo_heart->data = &philo;
	if (!*philo_heart)
	{
		*philo_heart = new_philo_heart;
	}
	else
	{
		new_next_philo_heart->next = *philo_heart;
		new_philo_heart->prev = (*philo_heart)->prev;
		(*philo_heart)->prev = new_next_philo_heart;
		(*philo_heart)->prev->next = new_philo_heart;
	}

}

int main (void)
{
	t_philo_heart	*philo_heart;
	int				count;
	char			**philo_name;
	t_philo			philo;

	//printf("%s\n", philo_name[1]);
	//ft_tabdup((char**)*(&(philo_name)));
	philo_name = NULL;
	{printf("bonjour\n");printf("les\n");printf("amis\n");}
	count = -1;
	philo_heart = NULL;
	ft_malloc_cmd(&philo_name, "Platon");
	ft_malloc_cmd(&philo_name, "Aristote");
	ft_malloc_cmd(&philo_name, "Héraclite");
	ft_malloc_cmd(&philo_name, "Epictète");
	ft_malloc_cmd(&philo_name, "Marc-Aurèle");
	ft_malloc_cmd(&philo_name, "Sénèque");
	ft_malloc_cmd(&philo_name, "Socrate");
	while (++count < NB_PHILO)
		ft_create_thread(&philo_heart, philo_name[count]);
	philo_heart = philo_heart->next;
	printf("[%s]\n", (char*)(*(t_philo*)philo_heart->data).name);
	philo_heart = philo_heart->next;
	philo_heart = philo_heart->next;
	printf("[%s]\n", (char*)(*(t_philo*)philo_heart->data).name);
	//printf("%s\n", philo.name);

	while (--count > 0)
	{
		//pthread_join (platon, NULL);
	}

	return 0;
}
