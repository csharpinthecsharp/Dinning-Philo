/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/04 03:58:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;   
    int left = p->id - 1;
    int right = (p->id) % p->data->n_philo;
    p->lastmeal = p->data->time_at_start;
    while (p->death == 1 && p->data->n_philo != 1)
    {
        long long t_current = time_ms();
        if (t_current - p->lastmeal > p->data->t_die)
        {
            print_lock(p, "Someone died");
            p->death = 0;
        }
        print_lock(p, "is thinking");
        pthread_mutex_lock(&p->data->forks[left]);
        print_lock(p, "has taken a fork");
        pthread_mutex_lock(&p->data->forks[right]);
        print_lock(p, "has taken a fork");
        usleep(p->data->t_eat);
        print_lock(p, "is eating");
        p->lastmeal = t_current;
        pthread_mutex_unlock(&p->data->forks[right]);
        pthread_mutex_unlock(&p->data->forks[left]);
        print_lock(p, "is sleeping");
        usleep(p->data->t_sleep);
    }
    return (NULL);
}

void *monitoring(void *arg)
{  
    t_philo *p = (t_philo *)arg;
    (void)p; 
    return (NULL);
}
