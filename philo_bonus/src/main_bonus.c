/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:21 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/30 22:53:26 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philosophers = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->num_meals = atoi(argv[5]);
	else
		data->num_meals = -1;
	data->start_time = get_time();
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philosophers)
		exit(1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philosophers);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED)
		exit(1);
	sem_unlink("/forks");
	sem_unlink("/print");
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		status;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	init_data(&data, argc, argv);
	start_simulation(&data);
	i = -1;
	while (++i < data.num_philosophers)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < data.num_philosophers)
				kill(data.philosophers[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(data.forks);
	sem_close(data.print);
	free(data.philosophers);
	return (0);
}
