/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/07 11:10:53 by ltrillar         ###   ########.fr       */
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
        if (print_lock(p, BLUE "is thinking" RESET, "💭", 0) == 1)
                return (NULL);
        if (left < right)
        {
            pthread_mutex_lock(&p->data->forks[left]);
            if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
            {
                pthread_mutex_unlock(&p->data->forks[left]);
                return (NULL);
            }
            pthread_mutex_lock(&p->data->forks[right]);
            if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
            {
                pthread_mutex_unlock(&p->data->forks[right]);
                pthread_mutex_unlock(&p->data->forks[left]);
                return (NULL);
            }
        }
        else
        {
            pthread_mutex_lock(&p->data->forks[right]);
            if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
            {
                return (NULL);
                pthread_mutex_unlock(&p->data->forks[right]);
            }
            pthread_mutex_lock(&p->data->forks[left]);
            if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
            {
                pthread_mutex_unlock(&p->data->forks[left]);
                pthread_mutex_unlock(&p->data->forks[right]);
                return (NULL);
            }
        }
        p->lastmeal = time_ms();
        if (print_lock(p, YELLOW "is eating" RESET, "🍔", 0) == 1)
            return (NULL);
        ft_usleep(p->data->t_eat);

        pthread_mutex_unlock(&p->data->forks[right]);
        pthread_mutex_unlock(&p->data->forks[left]);

        if (print_lock(p, GREEN "is sleeping" RESET, "💤", 0) == 1)
            return (NULL);
        ft_usleep(p->data->t_sleep);
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
                p->data->death = 0;
                print_lock(&p[i], "\e[31mdied" RESET, "⚰️ ", 1);
                return (NULL);
            } 
            ft_usleep(1);
            i++;
        }
    }
    return (NULL);
}
