/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:35:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 01:47:50 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int init_data(t_data *d, char *joker[])
{
    d->number_of_philosophers = atoi(joker[1]);
    d->time_to_die = atoi(joker[2]);
    d->time_to_eat = atoi(joker[3]);
    d->time_to_sleep = atoi(joker[4]);
    d->timestamp_in_ms = get_time();
    int i = 0;
    d->philo = malloc(sizeof(t_philo) * d->number_of_philosophers);
    d->forks = malloc(sizeof(pthread_mutex_t) * d->number_of_philosophers);
    if (!d->philo || !d->forks)
        return (1);
    while (i < d->number_of_philosophers)
    {
        pthread_mutex_init(&d->forks[i], NULL);
        d->philo[i].id = i + 1;
        d->philo[i].left_fork = &d->forks[i];
        d->philo[i].right_fork = &d->forks[(i + 1) % d->number_of_philosophers];
        d->philo[i].data = d;
        pthread_create(&d->philo[i].thread, NULL, &routine, &d->philo[i]);
        i++;
    }

    return (0);
}

long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

