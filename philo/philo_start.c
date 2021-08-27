/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/08/27 19:39:52 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *round_life(void *philo)
{
	t_philo *copy_ph;
	
	copy_ph = (t_philo *)philo;
	if (copy_ph->num_phil % 2 == 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&copy_ph->data.forks[copy_ph->left_fork]);
		copy_ph->data.current_time = get_time();
		print_messange(copy_ph->data.current_time, copy_ph->num_phil, "take a left fork.");
		pthread_mutex_lock(&copy_ph->data.forks[copy_ph->right_fork]);
		copy_ph->data.current_time = get_time();
		print_messange(copy_ph->data.current_time, copy_ph->num_phil, "take a right fork.");
		copy_ph->num_eat++;
		copy_ph->start_eat = get_time();
		print_messange(copy_ph->start_eat, copy_ph->num_phil, "is eating.");
		ft_usleep(copy_ph->data.time_to_eat);
		pthread_mutex_unlock(&copy_ph->data.forks[copy_ph->left_fork]);
		pthread_mutex_unlock(&copy_ph->data.forks[copy_ph->right_fork]);
		copy_ph->start_sleep = get_time();
		print_messange(copy_ph->start_sleep, copy_ph->num_phil, "is sleeping.");
		ft_usleep(copy_ph->data.time_to_sleep);
		print_messange(copy_ph->data.current_time, copy_ph->num_phil, "if thinking.");
	}
}

void start_play(t_info *info, t_philo *philo)
{
	int i;

	i = 1;
	while (i <= info->number_philo)
	{
		pthread_create(&philo[i].tread, NULL, &round_life, (void *)(&philo[i]));
		pthread_detach(philo[i].tread);
	}
}

void init_phill(t_info *info, t_philo *philo) // инициализируем структуру каждого философа
{
	int i;

	i = 1;
	while (i <= info->number_philo)
	{
		philo[i].num_phil = i;
		philo->left_fork = philo->num_phil - 1;
		if (philo->left_fork < 1)
			philo->left_fork = info->number_philo;
		philo->right_fork = philo->num_phil;
		pthread_mutex_init(&info->forks[philo->left_fork], NULL);
		pthread_mutex_init(&info->forks[philo->right_fork], NULL);
		philo[i].num_eat = 0;
		i++;
	}
}

int before_a_game(t_info *info, t_philo *philo) // подготовка к началу "голодных игр" плодим необходимое количество структур под каждого философа и узнаем время начала.
{
	philo = (t_philo *)ft_calloc(sizeof(t_philo), info->number_philo);
	if (!philo)
		return (1);
	info->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), info->number_philo);
	if (!info->forks)
		return (1);
	info->time_to_start = get_time();
	return (0);
}

int init_struct(t_info *info, int argc, char **argv) // инициализация структур, присвоение переданных данных.
{
	info->number_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->number_of_philo_eat = -1;
	if (argc == 6)
		info->number_of_philo_eat = ft_atoi(argv[5]);
	if (!(info->number_philo > 0 && info->number_philo <= 200))
		return (1);
	if (info->time_to_die < 0 || info->time_to_eat < 0 
		|| info->time_to_sleep < 0 || info->number_of_philo_eat < -1)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_info info;
	t_philo *philo;
	
	if (argc != 5 && argc != 6)
		return (1);
	if ((init_struct(&info, argc, argv)) != 0)
		return (1);
	before_a_game(&info, &philo);
	init_phill(&info, &philo);
	start_play(&info, &philo);
	return (0);
}