/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:32:35 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:49:00 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int init_info(t_info *info, int argc, char **argv)
{
    info->num_philosophers = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]);
    info->time_to_sleep = ft_atoi(argv[4]);
    info->num_times_must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
    info->died = 0;
    info->start_time = get_time();

    info->philosophers = malloc(sizeof(t_philo) * info->num_philosophers);
    if (!info->philosophers)
        return (-1);

    sem_unlink("/forks");
    info->forks = sem_open("/forks", O_CREAT, 0644, info->num_philosophers);
    if (info->forks == SEM_FAILED)
        return (-1);

    sem_unlink("/print_lock");
    info->print_lock = sem_open("/print_lock", O_CREAT, 0644, 1);
    if (info->print_lock == SEM_FAILED)
        return (-1);

    for (int i = 0; i < info->num_philosophers; i++)
    {
        info->philosophers[i].id = i + 1;
        info->philosophers[i].info = info;
        info->philosophers[i].last_meal = info->start_time;
    }

    return (0);
}

int start_simulation(t_info *info)
{
    for (int i = 0; i < info->num_philosophers; i++)
    {
        info->philosophers[i].pid = fork();
        if (info->philosophers[i].pid < 0)
            return (-1);
        if (info->philosophers[i].pid == 0)
            philosopher(&info->philosophers[i]);
    }

    wait_for_philosophers(info);
    return (0);
}

void wait_for_philosophers(t_info *info)
{
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            info->died = 1;
            for (int i = 0; i < info->num_philosophers; i++)
                kill(info->philosophers[i].pid, SIGKILL);
            break;
        }
    }
}

void cleanup(t_info *info)
{
    sem_close(info->forks);
    sem_unlink("/forks");
    sem_close(info->print_lock);
    sem_unlink("/print_lock");
    free(info->philosophers);
}
