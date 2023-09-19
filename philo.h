#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	long long			time;
	int					name;
	int					nb_eat;
	long long			finisheat;
	pthread_mutex_t		*left;
	pthread_mutex_t		finish;
	pthread_mutex_t		*right;
	pthread_t			create;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					nb_philo_eat;
	int					dead;
	int					finsh;
	pthread_mutex_t		die;
	pthread_mutex_t		nb_eat_lock;
	pthread_mutex_t		print;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}						t_data;

int						verif_args(char **argv);
int						verif_all_numbers(char **argv);
long					ft_atoi_long(char *argv);
int						verif_int(char **argv);
int						ft_atoi(char *str);

#endif