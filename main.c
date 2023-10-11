// Selon moi :
// 1. parcing
// 1-a verifier le nombre d argument et  la validite des arguments
// 1-b verifier les limites des arguments
// 1-c transformer les arguments avec les bonnes unite
// 1-d initialisation des variable

// 2. Philosophers
// 2-a pensez a la bonne structrure pour les philosophers
//     1 philosopher -> 1 fourchette, 1 ou 2 pointeur vers les philosopher,
//	le temps avant de mourir,
//     le nombre de fois ou le philosopher a mange, le temps de repos
// 2-b l affichage des informations demande dans le sujet

// 3. thread
// 3-a gerer les differents thread et bloquer les variables qu il faut acceder

// 4. cree une fonctions qui free
#include "philo.h"

void 	init_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;	// initialiser chaque philo avec une fourchette de type mutex
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0; // repartir les fourchettes 
	while(i < data->nb_philo)
	{
		philo[i].name = i;
		philo[i].nb_eat = 0;
		philo[i].finisheat = fc_time();
		philo[i].time= fc_time();
		pthread_mutex_init(&philo[i].finish, NULL);
		if (i == data->nb_philo - 1)
			philo[i].right = &data->fork[0];
		else
			philo[i].right = &data->fork[i + 1];
		philo[i].left = &data->fork[i];
		philo[i].data = data;
		i++;
	}
}

int	fork_eat(t_philo *philo)
{
	if (philo -> name % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		if (print_msg(philo, "Take a fork"))
			return (ft_unlock(philo, 1), 1);
		if (philo->left == philo->right)
			return (ft_unlock(philo, 1), 1);
		pthread_mutex_lock(philo->right);
		if (print_msg(philo, "Take a fork"))
			return (ft_unlock(philo, 2), 1);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		if (print_msg(philo, "Take a fork"))
			return (ft_unlock(philo, 0), 1);
		pthread_mutex_lock(philo->left);
		if (print_msg(philo, "Take a fork"))
			return (ft_unlock(philo, 2), 1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (fork_eat(philo))
		return (1);
	pthread_mutex_lock(& philo->finish);
	philo->finisheat = fc_time();
	pthread_mutex_unlock(& philo->finish);
	if (print_msg(philo, "is eating"))
		return (ft_unlock(philo, 2), 1);
	dors_lancien(philo->data->tt_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->nb_eat == philo->data->nb_philo_eat)
	{
		pthread_mutex_lock(&philo->data->nb_eat_lock);
		philo->data->finish++;
		pthread_mutex_unlock(&philo->data->nb_eat_lock);
		return (1);
	}
	return (0);
}

long int	fc_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); // convertir des micro aux millisecondes
}

int	dors_lancien(long int duree)
{
	long	start;

	start = fc_time();
	while (fc_time() - start < duree)
		usleep(10);
	return (1);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->name % 2 == 0)
		dors_lancien(philo->data->tt_eat * 0.8);
	while (1)
	{
		if (philo->data->nb_philo % 2 && philo->nb_eat)
			dors_lancien(philo->data->tt_die * 0.25);
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (print_msg(philo, "is thinking"))
			break ;
	}
	return (NULL);
}

void alloc(t_data *data, char **argv, int argc)
{
	t_philo *philo;
	int i;

	i = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat =  ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argc == 6)
		data->nb_philo_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->die, NULL);
	pthread_mutex_init(&data->nb_eat_lock, NULL);
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->fork = malloc(sizeof(pthread_mutex_t)* data->nb_philo);
	init_philo(philo, data);
	data->philo = philo;
	while(i < data->nb_philo)
	{
		pthread_create(&philo[i].create, NULL, &routine, &data->philo[i]);
		i++;
	}
	i = 0;
	vision(data);
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].create, NULL);
		i++;
	}
}


int	main(int argc, char **argv)
{
	t_data data;
	if (argc != 5 && argc != 6)
	{
		write(2, "Arguments invalides\n", 21);
		return (1);

	}
	if (verif_args(argv) == 1)
	{
		write(2, "Arguments invalides\n", 21);
		exit(1);
	}
	if (ft_atoi(argv[1]) == 0)
		exit(1);
	memset(&data, 0, sizeof(t_data));
	alloc(&data, argv, argc);
	printf("%d \n", data.nb_philo);
}