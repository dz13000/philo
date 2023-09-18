#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;

    while(str[i] >= 9 && str[i] <= 13 || (str[i] == 32))
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