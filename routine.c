/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:51:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 14:00:12 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (1) // loop until a stop condition
    {    
        
        if (philo->data->number_of_philosophers == 1) {
            printf("%lld %d has taken a fork\n", current_time(philo->data), philo->id);
            usleep(philo->data->time_to_die);  // Wait for death time
            printf("%lld %d died\n", current_time(philo->data), philo->id);
            return NULL;
        }
        // Pick up forks
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->right_fork);
            printf("%lld %d has taken a fork\n", current_time(philo->data), philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("%lld %d has taken a fork\n", current_time(philo->data), philo->id);
        } else {
            pthread_mutex_lock(philo->left_fork);
            printf("%lld %d has taken a fork\n", current_time(philo->data), philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("%lld %d has taken a fork\n", current_time(philo->data), philo->id);
        }
        
        // Eat
        printf("%lld %d is eating\n", current_time(philo->data), philo->id);
        philo->last_meal = current_time(philo->data);
        usleep(philo->data->time_to_eat * 1000);
        
        // Put down forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        
        // Sleep
        printf("%lld %d is sleeping\n", current_time(philo->data), philo->id);
        usleep(philo->data->time_to_sleep * 1000);
        
        // Think
        printf("%lld %d is thinking\n", current_time(philo->data), philo->id);
    }
    return (NULL);
}


void *monitor(void *arg)
{
    t_data *d = (t_data *)arg;
    while (1)
    {
        int i = 0;
        while (i < d->number_of_philosophers)
        {
            if (current_time(d) - d->philo[i].last_meal > d->time_to_die)
            {
                printf("%lld %d died\n", current_time(d), d->philo[i].id);
                d->death = 1;
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}
long long current_time(t_data *d)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((long long)(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - d->timestamp_in_ms);
}