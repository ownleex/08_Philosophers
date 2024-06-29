/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:32:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:55:55 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void philosopher(t_philo *philo)
{
    pthread_t monitor_thread;

    philo->last_meal = get_time();
    if (pthread_create(&monitor_thread, NULL, monitor_philosopher, philo) != 0)
        exit(1);
    pthread_detach(monitor_thread);

    while (!philo->info->died)
    {
        if (take_forks(philo) != 0)
            break;
        if (eat(philo) != 0)
            break;
        if (sleep_and_think(philo) != 0)
            break;
    }
    exit(0);
}

int take_forks(t_philo *philo)
{
    if (philo->info->died)
        return (-1);
    sem_wait(philo->info->forks);
    print_action(philo->info, philo->id, "has taken a fork");
    sem_wait(philo->info->forks);
    print_action(philo->info, philo->id, "has taken a fork");
    return (0);
}

int eat(t_philo *philo)
{
    if (philo->info->died)
        return (-1);
    print_action(philo->info, philo->id, "is eating");
    philo->last_meal = get_time();
    printf("Philosopher %d last meal updated to: %ld\n", philo->id, philo->last_meal);
    usleep(philo->info->time_to_eat * 1000);
    sem_post(philo->info->forks);
    sem_post(philo->info->forks);
    return (0);
}

int sleep_and_think(t_philo *philo)
{
    if (philo->info->died)
        return (-1);
    print_action(philo->info, philo->id, "is sleeping");
    usleep(philo->info->time_to_sleep * 1000);
    print_action(philo->info, philo->id, "is thinking");
    return (0);
}
