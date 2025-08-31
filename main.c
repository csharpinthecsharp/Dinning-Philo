/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 14:59:09 by ltrillar          #+#    #+#             */
/*   Updated: 2025/08/31 21:24:25 by ltrillar         ###   ########.fr       */
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
    free_mutex(d);
    return (0);
}
