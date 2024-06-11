/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:15:01 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/10 18:18:19 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_positive(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	int	i;
	int	num_of_philos;

	i = 1;
	while (i < argc)
	{
		if (!is_positive(argv[i]) || ft_atol(argv[i]) <= 0)
			return (error("Err: All arguments must be positive integers.\n"));
		i++;
	}
	num_of_philos = ft_atol(argv[1]);
	if (num_of_philos > 200)
		return (error("Err: Number of philosophers must not exceed 200.\n"));
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error("Err: Wrong argument count\n"));
	if (check_arguments(argc, argv))
		return (1);
	// Code principal ici
	return (0);
}