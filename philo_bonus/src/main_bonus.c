/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:21 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 19:36:13 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_semaphores(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philosophers);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->sem_alive = sem_open("/alive", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED || \
	data->sem_alive == SEM_FAILED)
	{
		if (data->forks != SEM_FAILED)
			sem_close(data->forks);
		if (data->print != SEM_FAILED)
			sem_close(data->print);
		if (data->sem_alive != SEM_FAILED)
			sem_close(data->sem_alive);
		free(data->philosophers);
		exit(1);
	}
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/alive");
}

static void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->start_time = get_time();
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if
		(!data->philosophers) exit(1);
	init_semaphores(data);
}

static void	monitor_philosophers(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			i = 0;
			while (i < data->num_philosophers)
			{
				kill(data->philosophers[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) > 0)
		return (1);
	init_data(&data, argc, argv);
	start_simulation(&data);
	monitor_philosophers(&data);
	clean_up(&data);
	return (0);
}
