/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/08/25 04:44:51 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void round_life(void *philo)
{
	t_philo *copy_ph;
	
	copy_ph = (t_philo *)philo;
	if (copy_ph->num_phil % 2 == 0)
		usleep(50);
	while (copy_ph->num_eat < copy_ph->data.number_of_philo_eat)
	{
		pthread_mutex_lock(&copy_ph->left_fork);
		printf("take a left fork");
		pthread_mutex_lock(&copy_ph->right_fork);
		printf("take a right fork");
		copy_ph->num_eat++;
	}
}

void start_play(t_info *info, t_philo *philo)
{
	int i;

	i = 1;
	while (i <= info->number_philo)
	{
		pthread_create(&philo[i].tread, NULL, &round_life, (void *)(&philo[i]));
		pthread_detach(&philo[i].tread);
	}
}

void init_fork(t_info *info, t_philo *philo)
{
	int i;

	i = 0;
	while (i < info->number_philo)
	{
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].right_fork, NULL);
		philo[i].num_eat = 0;
		philo[i].num_phil = i;
		philo[i].start_eat = get_time();
		i++;
	}
}

void init_struct(t_info *info, int argc, char **argv)
{
	info->number_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->number_of_philo_eat = ft_atoi(argv[5]);
}

int main(int argc, char **argv)
{
	t_info info;
	t_philo *philo;
	
	if (argc != 5 && argc != 6)
		return (1);
	init_struct(&info, argc, argv);
	philo = (t_philo *)ft_calloc(sizeof(t_philo), info.number_philo);
	if (!philo);
		return(1);
	init_fork(&info, philo);
	start_play(&info, &philo);
	return (0);
}