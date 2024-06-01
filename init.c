/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:57:38 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 10:00:27 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int alloc_init(t_data **data, pthread_mutex_t **forks, char *av)
{
    (*data)->n_philos = ft_atoi(av);
    if(!(*data)->n_philos)
        return(0);
    *forks = malloc(sizeof(pthread_mutex_t) * (*data)->n_philos);
    (*data)->philos = malloc(sizeof(t_philo) * (*data)->n_philos);
    if(!*forks || !(*data)->philos)
    {
        free(*forks);        
        free((*data)->philos);
        free(*data);
        ft_error();        
        return(0);
    }
    return(1);
}
void    init_forks(pthread_mutex_t *forks, int n_philos)
{
    int i;

    i = 0;
    while(i < n_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}
void init_philos(t_data *data, pthread_mutex_t *forks)
{
    t_philo *philos;
    int i;

    philos = data->philos;
    i = 0;
    while (i < data->n_philos)
    {
        philos[i].id = i + 1;
        philos[i].meal = 0;
        philos[i].start_time = 0;
        philos[i].data = data;
        philos[i].l_fork = &forks[i];
        philos[i].r_fork = &forks[(i + 1) % data->n_philos];
        pthread_mutex_init(&philos[i].philo, NULL);
        i++;
    }
}
void    data_init(t_data *data, pthread_mutex_t *forks, char **av, int ac)
{
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    data->meals = -1;
    if(ac == 6)
        data->meals = ft_atoi(av[5]);
    data->dead = 0;
    data->show_time = 0;
    init_forks(forks, data->n_philos);
    init_philos(data, forks);
    data->show_time = time_ms();
    pthread_mutex_init(&data->monitor, NULL);
    pthread_mutex_init(&data->print, NULL);
}

void    create_wait_threads(t_data *data)
{
    t_philo *philo;
    int i;

    i = -1;
    philo = data->philos;
    pthread_create(&data->thread, NULL, check, data);
    while (++i < data->n_philos)
        pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
    i = -1;
    while (++i < data->n_philos)
        pthread_join(philo[i].thread, NULL);
    pthread_join(data->thread, NULL);
}
