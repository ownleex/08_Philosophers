/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:33:07 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:37:12 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo
{
    int             id;
    pid_t           pid;
    long            last_meal;
    struct s_info   *info;
} t_philo;

typedef struct s_info
{
    int             num_philosophers;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             num_times_must_eat;
    long            start_time;
    t_philo         *philosophers;
    sem_t           *forks;
    sem_t           *print_lock;
    int             died;
} t_info;

int init_info(t_info *info, int argc, char **argv);
int start_simulation(t_info *info);
void wait_for_philosophers(t_info *info);
void cleanup(t_info *info);
void philosopher(t_philo *philo);
int take_forks(t_philo *philo);
int eat(t_philo *philo);
int sleep_and_think(t_philo *philo);
int error(char *msg);
long get_time(void);
void print_action(t_info *info, int id, char *action);
int ft_atoi(const char *str);
void *monitor_philosopher(void *arg);

#endif
