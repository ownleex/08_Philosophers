/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 02:06:15 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 02:10:00 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_arg(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
	int	result;

	result = 0;
	if (ft_atoi(argv[1]) > MAX_PHILO || ft_atoi(argv[1]) <= 0 || \
	check_arg(argv[1]))
		result = write(2, "Invalid philosophers number\n", 29);
	if (ft_atoi(argv[2]) <= 0 || check_arg(argv[2]))
		result = write(2, "Invalid time to die\n", 21);
	if (ft_atoi(argv[3]) <= 0 || check_arg(argv[3]))
		result = write(2, "Invalid time to eat\n", 21);
	if (ft_atoi(argv[4]) <= 0 || check_arg(argv[4]))
		result = write(2, "Invalid time to sleep\n", 23);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg(argv[5])))
		result = write(2, "Invalid count of meals per philosopher\n", 40);
	return (result);
}
