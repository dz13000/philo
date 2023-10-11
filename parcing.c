#include "philo.h"

int	verif_all_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] == '+')
				j++;
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

long	ft_atoi_long(char *argv)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while ((argv[i] >= 9 && argv[i] <= 13) || argv[i] == 32)
		i++;
	if (argv[i] == '+')
		i++;
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		res = res * 10 + argv[i] - 48;
		i++;
	}
	return (res);
}

int	verif_int(char **argv)
{
	int		i;
	long	nb;

	i = 1;
	while (argv[i])
	{
		nb = ft_atoi_long(argv[i]);
		if (nb > 2147483647)
			return (1);
		if (nb < 0)
			return (1);
		i++;
	}
	return (0);
}

int	verif_args(char **argv)
{
	if (verif_all_numbers(argv) == 1)
		return(1);
	if (verif_int(argv) == 1)
		return(1);
		
		
	return (0);
}