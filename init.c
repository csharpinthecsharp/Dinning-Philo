/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:11:20 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 22:49:42 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int init_philo_data(t_philo *p)
{
    (void)p;
    
    p->data = malloc(sizeof(p->data));
    if (!p->data)
        return (1);

    p->data->n_philo = 0;
    p->data->t_die = 0;
    p->data->t_eat = 0;
    p->data->t_sleep = 0;
    p->data->n_eat_max = 0;

    return (0);
}

int init_struct(t_philo *p, char *joker[])
{
    (void)joker;
    if (init_philo_data(p) == 1)
        return (1);
    return (0);
}
