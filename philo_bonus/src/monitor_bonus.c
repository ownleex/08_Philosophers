/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:39 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 02:34:32 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks_and_eat(t_philosopher *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->sem_alive);
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->sem_alive);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleep_and_think(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_status(philo, "is thinking");
}

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

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		exit(1);
	pthread_detach(tid);
	pthread_join(tid, NULL);
	while (1)
	{
		take_forks_and_eat(philo);
		sleep_and_think(philo);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].data = data;
		data->philosophers[i].last_meal = get_time();
		data->philosophers[i].pid = fork();
		if (data->philosophers[i].pid == 0)
		{
			philosopher_routine(&data->philosophers[i]);
			exit(0);
		}
		i++;
	}
}
