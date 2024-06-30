/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:52 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 00:01:25 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_up(t_data *data)
{
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print != SEM_FAILED)
		sem_close(data->print);
	if (data->sem_alive != SEM_FAILED)
		sem_close(data->sem_alive);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/alive");
	if (data->philosophers)
		free(data->philosophers);
}

int	ft_atoi(char *str)
{
	long		res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int time_in_ms)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < (long long)time_in_ms)
		usleep(100);
}
