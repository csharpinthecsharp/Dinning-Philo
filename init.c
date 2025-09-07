/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:11:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/06 19:29:31 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int init_philo(t_philo **p, int n)
{
    *p = malloc(sizeof(t_philo) * 10); // A FIX LE VRAI NOMBRE
    if (!*p)
        return (1);

    t_data *data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    data->n_philo = 0;
    data->t_die = 0;
    data->t_eat = 0;
    data->t_sleep = 0;
    data->n_eat_max = 0;
    data->time_at_start = time_ms();
    data->death = 1;
    data->eye = 0;
    
    int i = 0;
    while (i < n)
    {
        (*p)[i].id = i + 1;
        (*p)[i].thread = NULL;
        (*p)[i].lastmeal = data->time_at_start;
        (*p)[i].data = data;
        i++;
    }
    return (0);
}

static void init_mutex(t_philo *p)
{
    pthread_mutex_init(&p->data->print_mutex, NULL);
    int i = 0;
    p->data->forks = malloc(sizeof(pthread_mutex_t) * p->data->n_philo);
    while (i < p->data->n_philo)
    {
        pthread_mutex_init(&p->data->forks[i], NULL);
        i++;
    }
}

static int init_threads(t_philo *p)
{
    int i;

    i = 0;
    init_mutex(p);
    p->thread = malloc(sizeof(pthread_t) * p->data->n_philo);
    if (!p->thread)
        return (1);
    if (pthread_create(&p->data->eye, NULL, &monitoring, p) != 0)
        return (1);  
    while (i < p->data->n_philo)
    {
        if (pthread_create(&p->thread[i], NULL, &routine, &p[i]) != 0)
            return (1);
        i++;
    }
    i = 0;
    if (pthread_join(p->data->eye, NULL))
        return (1);
    while (i < p->data->n_philo)
    {
        if (pthread_join(p->thread[i], NULL))
            return (1);
        i++;
    }

    return (0);
}

int init_struct(t_philo **p, char *joker[], int ac)
{
    (void)joker;
    int n;
    
    n = ac;
    if (init_philo(p, n) == 1)
        return (1);
    if (start_check(*p, joker, ac) == 1)
        return (1);
    if (init_threads(*p) == 1)
        return (1);
    return (0);
}
