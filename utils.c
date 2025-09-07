/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:27:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/06 19:22:09 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

long long time_ms(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

int print_lock(t_philo *p, char *str, char *emoji, int state)
{
    if (p->data->death == 0 && state == 0)
        return (1);
    pthread_mutex_lock(&p->data->print_mutex);
    long long t_current = time_ms();
    long long t_elapsed = (t_current - p->data->time_at_start);
    printf(" %s [%lld]-> %d: %s \n", emoji, t_elapsed, p->id, str);
    pthread_mutex_unlock(&p->data->print_mutex);
    return (0);
}

void free_and_exit(t_philo *p)
{   
    pthread_mutex_destroy(&p->data->print_mutex);
    pthread_mutex_destroy(p->data->forks);
    free(p);
    free(p->data);
}

void    ft_usleep(size_t mls)
{
    size_t  start;

    start = time_ms();
    while (time_ms() - start < mls)
        usleep(500);
}