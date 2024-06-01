/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:05:15 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 10:07:15 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    one_philo(t_philo *p)
{
    pthread_mutex_lock(p->l_fork);
    print("taking l_fork\n", p);
    pthread_mutex_lock(&p->philo);
    p->start_time = time_ms();
    p->meal++;
    pthread_mutex_unlock(&p->philo);
    while(is_die(p->data));
    pthread_mutex_unlock(p->l_fork);
}
void    eating(t_philo *p)
{
    t_data *data;

    data = p->data;
    pthread_mutex_lock(p->l_fork);
    print("taking l_fork\n", p);
    pthread_mutex_lock(p->r_fork);
    print("taking r_fork\n", p);
    pthread_mutex_lock(&p->philo);
    p->start_time = time_ms();
    p->meal++;
    pthread_mutex_unlock(&p->philo);
    print("eating\n", p);
    ft_usleep(data->t_eat, data);
    pthread_mutex_unlock(p->r_fork);
    pthread_mutex_unlock(p->l_fork);
}


void    sleeping(t_philo *p)
{
    t_data *data;

    data = p->data;
    print("sleeping\n", p);
    ft_usleep(data->t_sleep, data);
}



void    thinking(t_philo *p)
{
    t_data *data;
    
    data = p->data;
    pthread_mutex_lock(&data->monitor);
    if(!data->dead)
        printf("%zu : id = %d : thinking\n", time_ms() - data->show_time, p->id);
    pthread_mutex_unlock(&data->monitor);
}

void    *routine(void *arg)
{
    t_data *data;
    t_philo *p;

    p = arg;
    data = p->data;
    if(p->id % 2 == 0)
        usleep(100);
    if(data->n_philos == 1)
    {
        one_philo(p);
        return NULL;
    }
    while(is_die(data))
    {
        eating(p);
        sleeping(p);
        thinking(p);
    }
    return NULL;
}