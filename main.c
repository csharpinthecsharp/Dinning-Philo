/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:59:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/01 01:47:49 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int ac, char *av[])
{
    if (ac != 5)
        return (1);
    
    t_data *d;
    t_data data;
    d = &data;

    if (init_data(d, av) == 1)
        return (1);
    int i = 0;
    while (i < d->number_of_philosophers)
    {
        pthread_join(d->philo[i].thread, NULL);
        i++;
    }
    free_mutex(d);
    return (0);
}
