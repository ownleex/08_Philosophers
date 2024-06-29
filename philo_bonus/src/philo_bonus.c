/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:31:24 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:55:08 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *monitor_philosopher(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        long time_now = get_time();
        long time_since_last_meal = time_now - philo->last_meal;

        printf("Philosopher %d checking: time_now=%ld, last_meal=%ld, time_since_last_meal=%ld, time_to_die=%ld\n",
               philo->id, time_now, philo->last_meal, time_since_last_meal, philo->info->time_to_die);

        if (time_since_last_meal > philo->info->time_to_die)
        {
            print_action(philo->info, philo->id, "died");
            philo->info->died = 1;
            sem_post(philo->info->forks); // To unblock if waiting
            sem_post(philo->info->forks); // To unblock if waiting
            exit(1);
        }
        usleep(5000); // Sleep for 5ms
    }
}

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        return (error("Invalid number of arguments"));
    t_info info;
    if (init_info(&info, argc, argv) != 0)
        return (error("Initialization error"));
    if (start_simulation(&info) != 0)
        return (error("Simulation error"));
    cleanup(&info);
    return (0);
}
