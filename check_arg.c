/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:14:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/07 18:24:48 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// CHECK FOR NUMBERS
static int	check_nb(char *joker[])
{
	int	i;
	int	j;

	i = 1;
	while (joker[i])
	{
		j = 0;
		while (joker[i][j])
		{
			if (joker[i][j] < '0' || joker[i][j] > '9')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_max_min(char *joker[], int pos)
{
	int		nbr;
	int		sign;
	size_t	i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (joker[pos][i] == ' ' || ('\t' <= joker[pos][i]
			&& joker[pos][i] <= '\r'))
		i++;
	if (joker[pos][i] == '+')
		i++;
	else if (joker[pos][i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= joker[pos][i] && joker[pos][i] <= '9')
	{
		nbr = nbr * 10 + joker[pos][i] - '0';
		i++;
	}
	if ((nbr * sign) > MAX_INT)
		return (-1);
	return (nbr * sign);
}

static int	attribute_int(int nb, int pos, t_philo *p)
{
	if (pos == 1)
		p->data->n_philo = nb;
	else if (pos == 2)
		p->data->t_die = nb;
	else if (pos == 3)
		p->data->t_eat = nb;
	else if (pos == 4)
		p->data->t_sleep = nb;
	else if (pos == 5)
		p->data->n_eat_max = nb;
	return (nb);
}

int	start_check(t_philo *p, char *joker[], int ac)
{
	int	i;
	int	value;

	i = 1;
	if (check_nb(joker) == 1)
		return (1);
	while (i < ac)
	{
		value = (check_max_min(joker, i));
		if (value == -1)
			return (1);
		attribute_int(value, i, p);
		i++;
	}
	return (0);
}
