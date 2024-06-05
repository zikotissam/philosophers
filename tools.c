/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:08:01 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 10:26:30 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_ms(void)
{
	struct timeval	tv;
	size_t			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000;
	return (milliseconds);
}

void	ft_error(void)
{
	printf("invalid arguments\n");
	printf("number_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep[number_of_times_each_philosopher_must_eat]");
}

void	ft_usleep(size_t time, t_data *data)
{
	size_t	start;
	int		f;

	f = 1;
	start = time_ms();
	while (time_ms() - start < time && f)
	{
		pthread_mutex_lock(&data->monitor);
		if (data->dead)
			f = 0;
		pthread_mutex_unlock(&data->monitor);
		usleep(500);
	}
}

void	print(char *msg, t_philo *p)
{
	t_data	*data;

	data = p->data;
	pthread_mutex_lock(&data->monitor);
	pthread_mutex_lock(&data->print);
	if (!data->dead)
		printf("%zu : id = %d : %s", time_ms() - data->show_time, p->id, msg);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_unlock(&data->monitor);
}
