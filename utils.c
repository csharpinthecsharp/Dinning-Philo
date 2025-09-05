/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:27:53 by ltrillar          #+#    #+#             */
/*   Updated: 2025/09/05 21:19:38 by ltrillar         ###   ########.fr       */
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

void print_lock(t_philo *p, char *str)
{
    pthread_mutex_lock(&p->data->print_mutex);
    long long t_current = time_ms();
    long long t_elapsed = (t_current - p->data->time_at_start);
    printf(" 🍃 [%lld]-> %d: %s \n", t_elapsed, p->id, str);
    pthread_mutex_unlock(&p->data->print_mutex);
}