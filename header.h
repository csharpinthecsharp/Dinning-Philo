#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define RESET "\033[0m"
#define RED   "\033[31m"
#define GRN   "\033[32m"
#define YEL   "\033[33m"
#define CYN   "\033[36m"
#define MAG   "\033[35m"

#define MAX_INT 32767

typedef struct s_data
{
    int n_philo;
    int t_die;
    int t_sleep;
    int t_eat;
    int n_eat_max;
    long long time_at_start;
}   t_data;

typedef struct s_philo
{
    pthread_t *thread;
    int id;
    struct s_data      *data;
    int death;
    pthread_mutex_t print_mutex;
}   t_philo;

/* init */
int init_struct(t_philo **p, char *joker[], int ac);
int start_check(t_philo *p, char *joker[], int ac);

/* routine */
void *routine(void *arg);
void *monitoring(void *arg);

/* utils */
int ft_strlen(char *str);
long long time_ms(void);
void print_lock(t_philo *p, char *str);

#endif
