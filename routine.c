/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/02 16:15:41 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;   
    while (p->death == 1)
    {
        print_lock(p, "coucou");
    }
    return (NULL);
}

void *monitoring(void *arg)
{  
    t_philo *p = (t_philo *)arg;
    (void)p; 
    return (NULL);
}
