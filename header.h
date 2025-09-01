/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:59:35 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 13:49:51 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int                   id;
    long long             last_meal;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    pthread_t monitor;   
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int death;
    long long timestamp_in_ms;
    long long starttime_in_ms;
    t_philo *philo;
    pthread_mutex_t *forks;
} t_data;


int init_data(t_data *d, char *joker[]);
void free_mutex(t_data *d);
void *routine(void *arg);
void *monitor(void *arg);
long long current_time(t_data *d);

#endif