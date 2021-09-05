/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/05 20:08:35 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int who_is_eat = 0;

void who_is_died(t_info *info)
{
    int i;

    i = 0;
    while (1)
    {
		if (i >= info->number_philo)
			i = 0;
        info->current_time = get_time();
        if (info->current_time - info->time_to_start - info->philo[i].start_eat > info->time_to_die)
		{
			print_messange(info->current_time - info->time_to_start, info->philo[i].num_phil, "is died.");
            return ;
		}
		if (who_is_eat == info->number_philo)
		{
			pthread_mutex_lock(&info->print_mess);
			printf("| %ld | - | %s |\n", info->current_time - info->time_to_start, "all are eating");
			pthread_mutex_unlock(&info->print_mess);
			return ;
		}
        i++;
    }
}

void *round_life(void *philo)
{
	t_philo *copy_ph;
	
	copy_ph = (t_philo *)philo;
	if (copy_ph->num_phil % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->left_fork]);
		copy_ph->data->current_time = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time - copy_ph->data->time_to_start, copy_ph->num_phil, "take a left fork.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->right_fork]);
		copy_ph->data->current_time = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time - copy_ph->data->time_to_start, copy_ph->num_phil, "take a right fork.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		
		copy_ph->data->current_time = get_time();
		copy_ph->start_eat = copy_ph->data->current_time - copy_ph->data->time_to_start;
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->start_eat, copy_ph->num_phil, "is eating.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		copy_ph->num_eat++;
		if (copy_ph->num_eat == copy_ph->data->number_of_philo_eat)
			who_is_eat++;
		
		ft_usleep(copy_ph->data->time_to_eat);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->left_fork]);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->right_fork]);
		copy_ph->start_sleep = get_time();
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->start_sleep - copy_ph->data->time_to_start, copy_ph->num_phil, "is sleeping.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
		ft_usleep(copy_ph->data->time_to_sleep);
		pthread_mutex_lock(&copy_ph->data->print_mess);
		print_messange(copy_ph->data->current_time - copy_ph->data->time_to_start, copy_ph->num_phil, "if thinking.");
		pthread_mutex_unlock(&copy_ph->data->print_mess);
	}
}

int start_play(t_info *info)
{
	int i;

	i = 0;
	while (i < info->number_philo)
	{
		if ((pthread_create(&info->philo[i].tread, NULL, &round_life, (void *)(&info->philo[i]))) != 0)
			return (1);
		pthread_detach(info->philo[i].tread);
		i++;
	}
	return (0);
}

void init_phill(t_info *info, int i) // инициализируем структуру каждого философа
{
	info->philo[i].num_phil = i + 1;
	if (info->philo[i].num_phil % 2 == 1)
	{
		info->philo[i].left_fork = i;
		info->philo[i].right_fork = info->philo[i].num_phil % info->number_philo;
	}
	else
	{
		info->philo[i].right_fork = i;
		info->philo[i].left_fork = info->philo[i].num_phil % info->number_philo;
	}
	info->philo[i].num_eat = 0;
	info->philo[i].data = info;
	info->philo[i].start_eat = 0;
}

int before_a_game(t_info *info) // подготовка к началу "голодных игр" плодим необходимое количество структур под каждого философа и узнаем время начала.
{
	int i;
	
	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_philo);
	if (!info->philo)
		return (1);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->number_philo);
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
	{
		print_errors(0);
		return (1);
	}
	if ((init_struct(&info, argc, argv)) != 0)
	{
		print_errors(1);
		return (1);
	}
	if ((before_a_game(&info)) != 0)
	{
		print_errors(2);
		return (1);
	}
	if ((start_play(&info)) != 0)
	{
		print_errors(3);
		return (1);
	}
	who_is_died(&info);
	return (0);
}