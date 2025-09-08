/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/08 18:05:05 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (print_lock(p, BLUE "is thinking" RESET, "💭", 0) == 1)
			break ;
		if (p->fork_left < p->fork_right)
		{
			if (take_forks(p, p->fork_left, p->fork_right, 0) == 1)
				break ;
		}
		else
		{
			if (take_forks(p, p->fork_left, p->fork_right, 1) == 1)
				break ;
		}
		if (print_lock(p, YELLOW "is eating" RESET, "🍔", 0) == 1)
			break ;
		if (eat_sleep(p) == 1)
			break;
		if (print_lock(p, GREEN "is sleeping" RESET, "💤", 0) == 1)
			break ;
		ft_usleep(p->data->t_sleep);
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < p->data->n_philo)
		{
			if (time_ms() - get_lastmeal(p) >= p[i].data->t_die)
			{
				handle_death(&p[i], 0);
				return (NULL);
			}
			if (finish_eating(&p[i]) == 1)
				return (NULL);
			ft_usleep(1);
			i++;
		}
	}
	return (NULL);
}
