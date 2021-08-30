/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/08/31 00:40:06 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *round_life(void *philo)
{
	t_philo *copy_ph;
	
	copy_ph = (t_philo *)philo;
	if (copy_ph->num_phil % 2 == 0)
		usleep(1000);
	while (1)
	{
		// write(1, "start\n", 7);
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->left_fork]);
		copy_ph->data->current_time = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time, copy_ph->num_phil, "take a left fork.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->right_fork]);
		copy_ph->data->current_time = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time, copy_ph->num_phil, "take a right fork.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		copy_ph->num_eat++;
		copy_ph->start_eat = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->start_eat, copy_ph->num_phil, "is eating.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		ft_usleep(copy_ph->data->time_to_eat);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->left_fork]);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->right_fork]);
		copy_ph->start_sleep = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->start_sleep, copy_ph->num_phil, "is sleeping.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		ft_usleep(copy_ph->data->time_to_sleep);
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time, copy_ph->num_phil, "if thinking.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		// write(1, "end\n", 5);
	}
}

void start_play(t_info *info)
{
	int i;

	i = 1;
	while (i <= info->number_philo)
	{
		// write(1, "error4.1\n", 10);
		pthread_create(&info->philo[i].tread, NULL, &round_life, (void *)(&info->philo[i]));
		// write(1, "error4.2\n", 10);
		pthread_detach(info->philo[i].tread);
		// write(1, "error4.3\n", 10);
		i++;
	}
}

void init_phill(t_info *info, int i) // инициализируем структуру каждого философа
{
	// while (i <= info->number_philo)
	// {
		// printf("number_philo = %d num_phil = %d\n", info->number_philo, info->philo[i].num_phil);
		info->philo[i].num_phil = i + 1;
		// printf("number_philo = %d num_phil = %d\n", info->number_philo, philo[i]->num_eat);
		info->philo[i].left_fork = info->philo[i].num_phil - 1;
		if (info->philo[i].left_fork < 1)
			info->philo[i].left_fork = info->number_philo;
		info->philo[i].right_fork = info->philo[i].num_phil;
		// pthread_mutex_init(&info->forks[info->philo[i].left_fork], NULL);
		// pthread_mutex_init(&info->forks[info->philo[i].right_fork], NULL);
		info->philo[i].num_eat = 0;
	// 	i++;
	// }
}

int before_a_game(t_info *info) // подготовка к началу "голодных игр" плодим необходимое количество структур под каждого философа и узнаем время начала.
{
	int i;
	
	i = 0;
	info->philo = (t_philo *)ft_calloc(sizeof(t_philo), info->number_philo);
	if (!info->philo)
		return (1);
	info->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), info->number_philo);
	if (!info->forks)
		return (1);
	while (i < info->number_philo)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->number_philo)
	{
		init_phill(info, i);
		i++;
	}
	pthread_mutex_init(&info->print_mess, NULL);
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
	
	if (argc != 5 && argc != 6)
		return (1);
	if ((init_struct(&info, argc, argv)) != 0)
		return (1);
	// write(1, "error1\n", 8);
	before_a_game(&info);
	// write(1, "error2\n", 8);
	// write(1, "error3\n", 8);
	start_play(&info);
	// write(1, "error4\n", 8);
	return (0);
}