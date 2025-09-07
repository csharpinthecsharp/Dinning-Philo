/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:20:00 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/06 18:45:49 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int main(int ac, char *av[])
{
    if (!(ac >= 5 && ac <= 6))
        return (1);

    t_philo philo;
    t_philo *p = &philo;
    if (init_struct(&p, av, ac) == 1)
        return (1);
    free_and_exit(p);
    return (0);
}

