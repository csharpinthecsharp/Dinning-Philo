/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:35:19 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/31 21:24:07 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int init_data(t_data *d, char *joker[])
{
    d->number_of_philosophers = atoi(joker[1]);
    d->time_to_die = atoi(joker[2]);
    d->time_to_eat = atoi(joker[3]);
    d->time_to_sleep = atoi(joker[4]);

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
        pthread_create(&d->philo[i].thread, NULL, &routine, &d->philo);
        printf("Creation du philo %d\n", d->philo[i].id);
        i++;
    }
    return (0);
}

