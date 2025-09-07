/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:06:41 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/07 18:50:06 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	take_forks(t_philo *p, int left, int right, int start)
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

void	eat_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mutex);
	p->lastmeal = time_ms();
	pthread_mutex_unlock(&p->meal_mutex);
	ft_usleep(p->data->t_eat);
	pthread_mutex_unlock(&p->data->forks[p->fork_left]);
	pthread_mutex_unlock(&p->data->forks[p->fork_right]);
	p->eat_count++;
}

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
		eat_sleep(p);
		if (print_lock(p, GREEN "is sleeping" RESET, "💤", 0) == 1)
			break ;
		ft_usleep(p->data->t_sleep);
	}
	return (NULL);
}

static long long	get_lastmeal(t_philo *p)
{
	long long	meal_time;

	pthread_mutex_lock(&p->meal_mutex);
	meal_time = p->lastmeal;
	pthread_mutex_unlock(&p->meal_mutex);
	return (meal_time);
}

void	*monitoring(void *arg)
{
	t_philo		*p;
	int			i;
	long long	meal;

	p = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < p->data->n_philo)
		{
			meal = get_lastmeal(p);
			if ((p[i].eat_count == p->data->n_eat_max && p->data->n_eat_max > 0)
				|| time_ms() - meal >= p[i].data->t_die)
			{
				pthread_mutex_lock(&p->data->death_mutex);
				p->data->death = 0;
				pthread_mutex_unlock(&p->data->death_mutex);
				print_lock(p, "\e[31mdied" RESET, "⚰️ ", 1);
				return (NULL);
			}
			ft_usleep(1);
			i++;
		}
	}
	return (NULL);
}
