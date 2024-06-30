/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:21 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/30 23:32:30 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_up(t_data *data)
{
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print != SEM_FAILED)
		sem_close(data->print);
	sem_unlink("/forks");
	sem_unlink("/print");
	if (data->philosophers)
		free(data->philosophers);
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
	if (!data->philosophers)
		exit(1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philosophers);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED)
	{
		if (data->forks != SEM_FAILED)
			sem_close(data->forks);
		if (data->print != SEM_FAILED)
			sem_close(data->print);
		free(data->philosophers);
		exit(1);
	}
	sem_unlink("/forks");
	sem_unlink("/print");
}


int	check_arg(char *str)
{
	while (*str)
		if (*str < '0' || *str++ > '9')
			return (1);
	return (0);
}

int	check_valid_args(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILO || ft_atoi(argv[1]) <= 0 \
	|| check_arg(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29));
	if (ft_atoi(argv[2]) <= 0 || check_arg(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21));
	if (ft_atoi(argv[3]) <= 0 || check_arg(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21));
	if (ft_atoi(argv[4]) <= 0 || check_arg(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23));
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg(argv[5]) == 1))
		return (write(2, "Invalid count of meals per philosopher\n", 40));
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		status;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) > 0)
		return (1);
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
	clean_up(&data);
	return (0);
}
