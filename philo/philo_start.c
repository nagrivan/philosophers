/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/16 18:20:58 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_play(t_info *info)
{
	int	i;

	i = 0;
	info->time_to_start = get_time(0);
	while (i < info->number_philo)
	{
		if ((pthread_create(&info->philo[i].tread, NULL,
					(void *)&round_life, &info->philo[i])) != 0)
			return (1);
		usleep(DELAY);
		i++;
	}
	i = 0;
	while (i < info->number_philo)
	{
		if ((pthread_detach(info->philo[i].tread) != 0))
			return (1);
		i++;
	}
	return (0);
}

int	before_a_game(t_info *info)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	**forks_pt;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_philo);
	if (!info->philo)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * info->number_philo);
	if (!forks)
		return (1);
	forks_pt = malloc(sizeof(pthread_mutex_t *) * info->number_philo);
	if (!forks_pt)
	{
		free(forks);
		return (1);
	}
	init_mut_phil(info, forks, forks_pt);
	free(forks);
	return (0);
}

int	preporat_game(t_info *info, int argc, char **argv)
{
	if ((init_struct(info, argc, argv)) != 0)
	{
		print_errors(1);
		return (1);
	}
	if ((before_a_game(info)) != 0)
	{
		ft_free(info);
		print_errors(2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		print_errors(0);
		return (1);
	}
	if ((preporat_game(&info, argc, argv)) != 0)
		return (1);
	if ((start_play(&info)) != 0)
	{
		print_errors(3);
		return (1);
	}
	who_is_died(&info);
	ft_free(&info);
	return (0);
}
