/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:59:35 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/31 21:14:00 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;   
}   t_philo;

typedef struct s_data
{
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    t_philo *philo;
    pthread_mutex_t *forks;
} t_data;


int init_data(t_data *d, char *joker[]);
void free_mutex(t_data *d);
void *routine(void *arg);


#endif