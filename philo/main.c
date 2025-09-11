/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:20:00 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/11 15:14:52 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char *av[])
{
	t_philo	philo;
	t_philo	*p;

	if (!(ac >= 5 && ac <= 6))
	{
		printf("%sError:\nUsage ./philo [ARG1], [ARG2], [ARG3], [ARG4],"
			"[*ARG5].", RED);
		return (1);
	}
	p = &philo;
	if (init_program(&p, av, ac) == 1)
		return (1);
	free_and_exit(p);
	return (0);
}
