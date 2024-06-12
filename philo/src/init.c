/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:35:54 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/12 17:29:19 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_table *table)
{
	int		i;

	printf("Allocating philosophers\n");
	table->philos = malloc(sizeof(t_philosopher) * table->num_of_philo);
	if (!table->philos)
		return (error("Err: Memory allocation failed.\n"));
	i = 0;
	while (i < table->num_of_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % \
		table->num_of_philo];
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].meals_eaten = 0;
		i++;
	}
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	printf("Allocating forks\n");
	table->forks = malloc(sizeof(t_fork) * table->num_of_philo);
	if (!table->forks)
		return (error("Err: Memory allocation failed.\n"));
	i = 0;
	while (i < table->num_of_philo)
	{
		printf("Initializing mutex for fork %d\n", i);
		if (pthread_mutex_init(&table->forks[i].mutex_fork, NULL))
		{
			printf("Mutex initialization failed for fork %d\n", i);
			return (error("Err: Mutex initialization failed.\n"));
		}
		printf("Mutex initialized for fork %d\n", i);
		i++;
	}
	return (0);
}

int	init_table(t_table *table, int argc, char **argv)
{
	printf("Initializing table\n");
	table->num_of_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_of_meals = ft_atol(argv[5]);
	else
		table->num_of_meals = -1;
	table->start_time = get_current_time();
	if (init_forks(table))
		return (1);
	if (init_philosophers(table))
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (error("Err: Print mutex initialization failed.\n"));
	if (pthread_mutex_init(&table->meal_check_mutex, NULL))
		return (error("Err: Meal check mutex initialization failed.\n"));
	return (0);
}
