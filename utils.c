#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;

    while((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
        i++;
    if(str[i] == '+')
        i++;
    while(str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    return(res);
}

int	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (verif_death(philo))
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	printf("%lld %d %s\n", fc_time() - philo->time, philo->name +1, msg);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

void	ft_unlock(t_philo *philo, int opt)
{
	if (opt == 0)
		pthread_mutex_unlock(philo->right);
	else if (opt == 1)
		pthread_mutex_unlock(philo->left);
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
}

int	ft_sleep(t_philo *philo)
{
	if (print_msg(philo, "is sleeping"))
		return (EXIT_SUCCESS);
	dors_lancien(philo->data->tt_sleep);
	return (EXIT_SUCCESS);
}

void	vision(t_data *data)
{
	int		i;
	long	time;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(& data->philo[i].finish);
			time = fc_time() - data->philo[i].finisheat;
			pthread_mutex_unlock(& data->philo[i].finish);
			if (time >= data->tt_die)
				return (ft_dead(data, i));
			pthread_mutex_lock(&data->nb_eat_lock);
			if (data->finish == data->nb_philo)
			{
				pthread_mutex_unlock(&data->nb_eat_lock);
				return ;
			}
			pthread_mutex_unlock(&data->nb_eat_lock);
		}
		usleep(100);
	}
}