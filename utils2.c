#include "philo.h"

int	verif_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->die);
	i = philo->data->dead;
	pthread_mutex_unlock(&philo->data->die);
	return (i);
}

void	ft_dead(t_data *data, int i)
{
	pthread_mutex_lock(& data->die);
	data->dead = 1;
	pthread_mutex_unlock(& data->die);
	pthread_mutex_lock(&data->print);
	printf("%lld %d Died\n", (fc_time() - data->philo[i].time),
		data->philo->name + 1);
	pthread_mutex_unlock(&data->print);
}