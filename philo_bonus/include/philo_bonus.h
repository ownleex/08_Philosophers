/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:37:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/01 19:36:06 by ayarmaya         ###   ########.fr       */
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

# define MAX_PHILO 200

typedef struct s_philosopher
{
	int				id;
	pid_t			pid;
	long long		last_meal;
	int				meals_eaten;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_data
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*sem_alive;
	long long		start_time;
	t_philosopher	*philosophers;
}	t_data;

long long	get_time(void);
void		ft_usleep(int time_in_ms);
void		start_simulation(t_data *data);
void		philosopher_routine(t_philosopher *philo);
int			check_valid_args(char **argv);
int			ft_atoi(char *str);
void		clean_up(t_data *data);
void		print_status(t_philosopher *philo, const char *status);
int			check_arg(char *str);
int			check_valid_args(char **argv);

#endif
