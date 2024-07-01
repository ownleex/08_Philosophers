/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:38:52 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 02:51:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philosopher *philo, const char *status)
{
	long long	time;

	time = get_time() - philo->data->start_time;
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", time, philo->id, status);
	sem_post(philo->data->print);
}

void	clean_up(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philosophers)
	{
		kill(data->philosophers[i].pid, SIGKILL);
		waitpid(data->philosophers[i].pid, NULL, 0);
	}
	sem_close(data->forks);
	sem_close(data->print);
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
