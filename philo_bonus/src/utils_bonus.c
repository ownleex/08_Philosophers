/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:32:58 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/06/29 16:52:10 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_action(t_info *info, int id, char *action)
{
    long timestamp;

    sem_wait(info->print_lock);
    timestamp = get_time() - info->start_time;
    if (!info->died)
        printf("%ld %d %s\n", timestamp, id, action);
    sem_post(info->print_lock);
}

int error(char *msg)
{
    printf("%s\n", msg);
    return (1);
}

int ft_atoi(const char *str)
{
    int i = 0;
    int res = 0;
    int sign = 1;

    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
        res = res * 10 + (str[i++] - '0');
    return (res * sign);
}
