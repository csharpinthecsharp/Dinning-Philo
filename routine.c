/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/06 16:47:06 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;   
    int left = p->id - 1;
    int right = (p->id) % p->data->n_philo;
    p->lastmeal = p->data->time_at_start;

    while (1)
    {
        pthread_mutex_lock(&p->data->death_mutex);
        if (p->data->death == 0) 
            return (NULL);
        pthread_mutex_unlock(&p->data->death_mutex);
        print_lock(p, "\x1b[34mis thinking\x1b[0m", "💭");
        if (left < right)
        {
            pthread_mutex_lock(&p->data->forks[left]);
            print_lock(p, "\x1b[35mhas taken a fork\x1b[0m", "​🥄​");
            pthread_mutex_lock(&p->data->forks[right]);
            print_lock(p, "\x1b[35mhas taken a fork\x1b[0m", "​🥄​");
        }
        else
        {
            pthread_mutex_lock(&p->data->forks[right]);
            print_lock(p, "\x1b[35mhas taken a fork\x1b[0m", "​🥄​");
            pthread_mutex_lock(&p->data->forks[left]);
            print_lock(p, "\x1b[35mhas taken a fork\x1b[0m", "​🥄​");
        }
        print_lock(p, "\x1b[33mis eating\x1b[0m", "🍔​");
        usleep(p->data->t_eat);
        p->lastmeal = time_ms();
        pthread_mutex_unlock(&p->data->forks[right]);
        pthread_mutex_unlock(&p->data->forks[left]);
        print_lock(p, "\x1b[32mis sleeping\x1b[0m", "💤");
        usleep(p->data->t_sleep);
    }
    return (NULL);
}

void *monitoring(void *arg)
{  
    t_philo *p = (t_philo *)arg;
    int i = 0;
    while (1)
    {
        i = 0;
        while (i < p->data->n_philo)
        {
            long long t_current = time_ms();
            if (t_current - p[i].lastmeal >= p[i].data->t_die)
            {
                print_lock(&p[i], "\e[31mdied", "⚰️");
                p->data->death = 0;
            } 
            i++;
            usleep(1000);
        }
    }
    return (NULL);
}
