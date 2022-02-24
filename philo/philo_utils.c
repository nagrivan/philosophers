/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:08:32 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/16 20:36:38 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_info *info)
{
	int		i;

	i = 0;
	if (info->philo)
	{
		while (i < info->number_philo)
		{
			if (info->philo[i].forks)
			{
				pthread_mutex_destroy(info->philo[i].forks
				[info->philo->first_fork]);
				pthread_mutex_destroy(info->philo[i].forks
				[info->philo->second_fork]);
			}
			i++;
		}
	}
	pthread_mutex_destroy(&info->time_eat);
	pthread_mutex_destroy(&info->print);
	free(info->philo->forks);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned int		res;

	i = 0;
	res = 0;
	if (!str || !str[0])
		return (-1);
	if ((ft_strlen(str)) > 10)
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res == 0)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void	ft_usleep(time_t time)
{
	while (time)
	{
		usleep(500);
		time--;
	}
}

time_t	get_time(time_t start)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (time_t)1000) + time.tv_usec / 1000 - start);
}
