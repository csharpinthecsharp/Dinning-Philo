/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/08 19:23:36 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	take_forks(t_philo *p, int left, int right, int start)
{
	int	temp;

	if (start == 1)
	{
		temp = left;
		left = right;
		right = temp;
	}
	pthread_mutex_lock(&p->data->forks[left]);
	if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
	{
		pthread_mutex_unlock(&p->data->forks[left]);
		return (1);
	}
	pthread_mutex_lock(&p->data->forks[right]);
	if (print_lock(p, MAGENTA "has taken a fork" RESET, "🥄", 0) == 1)
	{
		pthread_mutex_unlock(&p->data->forks[right]);
		pthread_mutex_unlock(&p->data->forks[left]);
		return (1);
	}
	return (0);
}

void	handle_death(t_philo *p, int state)
{
	if (state == 0)
	{
		pthread_mutex_lock(&p->data->death_mutex);
		p->data->death = 0;
		pthread_mutex_unlock(&p->data->death_mutex);
		print_lock(p, "\e[31mdied" RESET, "⚰️ ", 1);
	}
}


int	eat(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	p->lastmeal = time_ms();
	p->eat_count++;
	pthread_mutex_unlock(&p->meal_mutex);
	ft_usleep(p->data->t_eat);
	pthread_mutex_unlock(&p->data->forks[p->fork_left]);
	pthread_mutex_unlock(&p->data->forks[p->fork_right]);
	if (finish_eating(p))
		return (1);
	return (0);
}

int finish_eating(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	if ((p->eat_count >= (p->data->n_eat_max)
	&& p->data->n_eat_max > 0)
	&& p->data->n_eat_max != MAX_INT)
	{
		pthread_mutex_unlock(&p->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->meal_mutex);
	return (0);
} 

long long	get_lastmeal(t_philo *p)
{
	long long	meal_time;

	pthread_mutex_lock(&p->meal_mutex);
	meal_time = p->lastmeal;
	pthread_mutex_unlock(&p->meal_mutex);
	return (meal_time);
}