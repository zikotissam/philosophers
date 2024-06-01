/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:53:59 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/06/01 10:10:17 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H


#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    pthread_mutex_t philo;
    pthread_t thread;
    size_t start_time;
    int meal;
    int id;
    t_data *data;
} t_philo;

typedef struct s_data
{
    pthread_mutex_t monitor;
    pthread_mutex_t print;
    pthread_t thread;
    size_t show_time;
    t_philo *philos;
    int t_sleep;
    int n_philos;
    int meals;
    int t_eat;
    size_t t_die;
    int dead;
} t_data;

int	ft_atoi(const char *nptr);
int    check_args(char **av, int ac);
size_t time_ms();
void    ft_error();
void    ft_usleep(size_t time, t_data *data);
void print(char *msg, t_philo *p);
void    eating(t_philo *p);
void    sleeping(t_philo *p);
int is_die(t_data *p);
void    thinking(t_philo *p);
void    *routine(void *arg);
int is_full(t_data *data);
int dead_check(t_data *data);
void    kill_all(t_data *p);
void    *check(void *arg);
int alloc_init(t_data **data, pthread_mutex_t **forks, char *av);
void    init_forks(pthread_mutex_t *forks, int n_philos);
void init_philos(t_data *data, pthread_mutex_t *forks);
void    data_init(t_data *data, pthread_mutex_t *forks, char **av, int ac);
void    create_wait_threads(t_data *data);
void    destroy_mutex(t_data *data, pthread_mutex_t *forks);
void    one_philo(t_philo *p);


#endif