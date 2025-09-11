/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:21:55 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/08 19:29:37 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define YELLOW "\x1b[33m"
# define GREEN "\x1b[32m"
# define RED "\x1b[31m"
# define RESET "\x1b[0m"

# define MAX_INT 32767

typedef struct s_data
{
	int				n_philo;
	long long		t_die;
	long long		t_sleep;
	long long		t_eat;
	long long		n_eat_max;
	long long		time_at_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_t		eye;
	int				death;
}					t_data;

typedef struct s_philo
{
	pthread_t		*thread;
	int				id;
	struct s_data	*data;
	long long		lastmeal;
	pthread_mutex_t	meal_mutex;
	int				fork_left;
	int				fork_right;
	long long		eat_count;
}					t_philo;

/* init */
int					init_program(t_philo **p, char *joker[], int ac);
int					start_check(t_philo *p, char *joker[], int ac);

/* routine */
void				*routine(void *arg);
void				*monitoring(void *arg);

/* utils */
long long			time_ms(void);
int					print_lock(t_philo *p, char *str, char *emoji, int state);
void				free_and_exit(t_philo *p);
void				ft_usleep(size_t mls);
int					check_max_min(char *joker[], int pos);
void				handle_death(t_philo *p);
int					take_forks(t_philo *p, int left, int right, int start);
int					eat(t_philo *p);
int					finish_eating(t_philo *p);
long long			get_lastmeal(t_philo *p);

#endif
