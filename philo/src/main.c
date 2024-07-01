/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:34:40 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 19:35:20 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_malloc(t_philo **philos, pthread_mutex_t **forks, int philo_num)
{
	*philos = (t_philo *)malloc(sizeof(t_philo) * philo_num);
	if (!*philos)
		return (write(2, "Memory allocation error for philosophers\n", 41));
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo_num);
	if (!*forks)
	{
		free(*philos);
		return (write(2, "Memory allocation error for forks\n", 33));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program			program;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					philo_num;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	if (check_valid_args(argv) > 0)
		return (1);
	philo_num = ft_atoi(argv[1]);
	if (ft_malloc(&philos, &forks, philo_num) > 0)
		return (1);
	init_program(&program, philos);
	init_forks(forks, philo_num);
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
