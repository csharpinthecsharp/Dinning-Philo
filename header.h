#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>

#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"

#define MAX_INT 32767

typedef struct s_data
{
    int n_philo;
    long long t_die;
    long long t_sleep;
    long long t_eat;
    long long n_eat_max;
    long long time_at_start;   
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    pthread_mutex_t death_mutex;
    pthread_t eye;
    int death;
}   t_data;



typedef struct s_philo
{
    pthread_t *thread;
    int id;
    struct s_data      *data;
    long long lastmeal;

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
int print_lock(t_philo *p, char *str, char *emoji, int state);
void free_and_exit(t_philo *p);
void    ft_usleep(size_t mls);

#endif
