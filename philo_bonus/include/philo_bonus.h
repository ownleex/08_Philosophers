/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:37:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/30 22:37:42 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philosopher
{
	int			id;
	pid_t		pid;
	long long	last_meal;
	int			meals_eaten;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_data
{
	int			num_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_meals;
	sem_t		*forks;
	sem_t		*print;
	long long	start_time;
	t_philosopher	*philosophers;
}	t_data;

long long	get_time(void);
void		ft_usleep(int time_in_ms);
void		start_simulation(t_data *data);
void		philosopher_routine(t_philosopher *philo);

#endif
