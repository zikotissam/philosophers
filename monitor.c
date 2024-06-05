/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:00:54 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 11:38:51 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_data *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&p->monitor);
	if (!p->dead)
		i = 1;
	pthread_mutex_unlock(&p->monitor);
	return (i);
}

void	kill_all(t_data *p)
{
	pthread_mutex_lock(&p->monitor);
	p->dead = 1;
	pthread_mutex_unlock(&p->monitor);
}

int	is_full(t_data *data)
{
	t_philo	*p;
	int		i;

	i = 0;
	p = data->philos;
	while (i < data->n_philos)
	{
		if (data->meals == -1)
			return (1);
		pthread_mutex_lock(&p[i].philo);
		if (p[i].meal < data->meals)
		{
			pthread_mutex_unlock(&p[i].philo);
			return (1);
		}
		pthread_mutex_unlock(&p[i].philo);
		i++;
	}
	kill_all(data);
	return (0);
}

int	dead_check(t_data *data)
{
	t_philo	*p;
	int		i;

	i = 0;
	p = data->philos;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&p[i].philo);
		if (p[i].start_time != 0 && time_ms() - p[i].start_time > data->t_die)
		{
			printf("[%zu] %d is die\n", time_ms() - data->show_time, p[i].id);
			pthread_mutex_unlock(&p[i].philo);
			return (1);
		}
		pthread_mutex_unlock(&p[i].philo);
		i++;
	}
	return (0);
}

void	*check(void *arg)
{
	t_data	*p;

	p = arg;
	while (is_full(p))
	{
		if (dead_check(p))
		{
			kill_all(p);
			break ;
		}
	}
	return (NULL);
}
