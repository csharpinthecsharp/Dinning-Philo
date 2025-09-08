/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:27:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/07 18:48:55 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long long	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	free_and_exit(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->data->n_philo)
	{
		pthread_mutex_destroy(&p->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&p->data->print_mutex);
	pthread_mutex_destroy(&p->data->death_mutex);
	free(p->data->forks);
	free(p->thread);
	free(p->data);
	free(p);
}
