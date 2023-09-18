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

void alloc(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat =  ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_philo_eat = ft_atoi(argv[5]);
}


int	main(int argc, char **argv, char **env)
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
	memset(&data, 0, sizeof(t_data));
	alloc(&data, argv, argc);
	printf("ok");
	printf("%d \n", data.nb_philo);
}