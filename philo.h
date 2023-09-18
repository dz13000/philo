#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
    int nb_philo;
    int tt_die;
    int tt_eat;
    int tt_sleep;
    int nb_philo_eat;
}   t_data;

int	verif_args(char **argv);
int	verif_all_numbers(char **argv);
long	ft_atoi_long(char *argv);
int	verif_int(char **argv);
int ft_atoi(char *str);


#endif