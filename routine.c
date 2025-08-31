/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:51:15 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 01:47:47 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    // Initialize last meal time
    philo->last_meal = get_time() - philo->data->timestamp_in_ms;
    
    if (philo->id % 2 == 0)
        usleep(1000); // stagger start for even philosophers
    
    while (1) // loop until a stop condition
    {
        // Check death condition
        if ((get_time() - philo->data->timestamp_in_ms) - philo->last_meal > philo->data->time_to_die) {
            printf("%lld %d died\n", get_time() - philo->data->timestamp_in_ms, philo->id);
            return NULL;
        }
        
        // Pick up forks
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->right_fork);
            printf("%lld %d has taken a fork\n", get_time() - philo->data->timestamp_in_ms, philo->id);
            pthread_mutex_lock(philo->left_fork);
            printf("%lld %d has taken a fork\n", get_time() - philo->data->timestamp_in_ms, philo->id);
        } else {
            pthread_mutex_lock(philo->left_fork);
            printf("%lld %d has taken a fork\n", get_time() - philo->data->timestamp_in_ms, philo->id);
            pthread_mutex_lock(philo->right_fork);
            printf("%lld %d has taken a fork\n", get_time() - philo->data->timestamp_in_ms, philo->id);
        }
        
        // Eat
        printf("%lld %d is eating\n", get_time() - philo->data->timestamp_in_ms, philo->id);
        philo->last_meal = get_time() - philo->data->timestamp_in_ms;
        usleep(philo->data->time_to_eat * 1000);
        
        // Put down forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        
        // Sleep
        printf("%lld %d is sleeping\n", get_time() - philo->data->timestamp_in_ms, philo->id);
        usleep(philo->data->time_to_sleep * 1000);
        
        // Think
        printf("%lld %d is thinking\n", get_time() - philo->data->timestamp_in_ms, philo->id);
    }
    return NULL;
}