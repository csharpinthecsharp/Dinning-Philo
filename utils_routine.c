/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/08 00:40:54 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_death(t_philo *p, int state)
{
	if (state == 0)
	{
		pthread_mutex_lock(&p->data->death_mutex);
		p->data->death = 0;
		pthread_mutex_unlock(&p->data->death_mutex);
		print_lock(p, "\e[31mdied" RESET, "⚰️ ", 1);
	}
	else
	{
		ft_usleep(1);
		pthread_mutex_lock(&p->data->death_mutex);
		p->data->death = 0;
		pthread_mutex_unlock(&p->data->death_mutex);
	}
}

int	print_lock(t_philo *p, char *str, char *emoji, int state)
{
	long long	t_current;
	long long	t_elapsed;

	pthread_mutex_lock(&p->data->death_mutex);
	if (p->data->death == 0 && state == 0)
	{
		pthread_mutex_unlock(&p->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->data->death_mutex);
	pthread_mutex_lock(&p->data->print_mutex);
	t_current = time_ms();
	t_elapsed = (t_current - p->data->time_at_start);
	printf(" %s [%lld]-> %d: %s \n", emoji, t_elapsed, p->id, str);
	pthread_mutex_unlock(&p->data->print_mutex);
	usleep(100);
	return (0);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = time_ms();
	while (time_ms() - start < mls)
		usleep(500);
}
