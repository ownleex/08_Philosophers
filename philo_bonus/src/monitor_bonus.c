/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:39 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 00:38:24 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philosopher	*philo;
	long long		time;

	philo = (t_philosopher *)arg;
	while (1)
	{
		time = get_time();
		if (time - philo->last_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->sem_alive);
			sem_wait(philo->data->print);
			printf("%lld %d died\n", time - philo->data->start_time, philo->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void philosopher_routine(t_philosopher *philo)
{
    pthread_t tid;

    if (pthread_create(&tid, NULL, &monitor, philo) != 0)
        exit(1);
    pthread_detach(tid);  // Assurez-vous de détacher le thread moniteur si nécessaire

    // Routine du philosophe
    while (1)
    {
        // Le philosophe prend une fourchette
        sem_wait(philo->data->forks);
        sem_wait(philo->data->print);
        printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
        sem_post(philo->data->print);

        // Le philosophe prend une autre fourchette et mange
        sem_wait(philo->data->forks);
        sem_wait(philo->data->print);
        printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->id);
        sem_wait(philo->data->sem_alive);
        printf("%lld %d is eating\n", get_time() - philo->data->start_time, philo->id);
        philo->last_meal = get_time();
        sem_post(philo->data->print);
        ft_usleep(philo->data->time_to_eat);
        sem_post(philo->data->sem_alive);
        sem_post(philo->data->forks);
        sem_post(philo->data->forks);

        // Le philosophe dort
        sem_wait(philo->data->print);
        printf("%lld %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
        sem_post(philo->data->print);
        ft_usleep(philo->data->time_to_sleep);

        // Le philosophe pense
        sem_wait(philo->data->print);
        printf("%lld %d is thinking\n", get_time() - philo->data->start_time, philo->id);
        sem_post(philo->data->print);
    }
    clean_up(philo->data);
}

void start_simulation(t_data *data)
{
    int i;

    for (i = 0; i < data->num_philosophers; i++)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].data = data;
        data->philosophers[i].last_meal = get_time();
        data->philosophers[i].pid = fork();
        if (data->philosophers[i].pid == 0)
        {
            philosopher_routine(&data->philosophers[i]);
            exit(0);  // S'assurer que le processus enfant se termine correctement
        }
    }
}

