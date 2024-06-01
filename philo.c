/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 00:59:28 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 10:08:28 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int    check_args(char **av, int ac)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(i < ac)
    {
        if(!av[i][0])
            return(0);
        while(av[i][j])
        {
            if(av[i][j] < '0' || av[i][j] > '9')
                return(0);
            j++;
        }
        i++;
        j = 0;
    }
    return(1);
}


void    destroy_mutex(t_data *data, pthread_mutex_t *forks)
{
    t_philo *p;
    int i;

    i = 0;
    p = data->philos;
    while (i < data->n_philos)
    {
        pthread_mutex_destroy(&p[i].philo);
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->monitor);
    
}

int main(int ac, char **av)
{
    pthread_mutex_t *forks;
    t_data *data;
    
    data = malloc(sizeof(t_data));
    if((ac != 5 && ac != 6) || !check_args(av, ac) || !data)
    {
        ft_error();
        return(1);
    }
    if(!alloc_init(&data, &forks, av[1]))
        return(1);
    data_init(data, forks, av, ac);
    create_wait_threads(data);
    destroy_mutex(data, forks);
    free(forks);
    free(data->philos);
    free(data);
}
