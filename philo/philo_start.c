/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:05:45 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/12 20:43:16 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void who_is_died(t_info *info)
{
    int i;

    i = 0;
    while (1)
    {
		usleep(500);
		if (i >= info->number_philo)
			i = 0;
        // info->current_time = get_time() - info->time_to_start;
		pthread_mutex_lock(&info->philo[i].data->time_eat);
        if (get_time() - info->time_to_start - info->philo[i].start_eat > info->time_to_die)
		{
			print_messange(get_time() - info->time_to_start, info->philo[i].num_phil, "is died."); //как убить потоки? дать команду
			pthread_mutex_unlock(&info->philo[i].data->time_eat);
			info->number_of_philo_eat = 0;
			return ;
		}
		if (info->who_is_eat == info->number_philo) //max_int
		{
			printf("| %ld | - | %s |\n", info->current_time, "all are eating");
			pthread_mutex_unlock(&info->philo[i].data->time_eat);
			return ;
		}
		pthread_mutex_unlock(&info->philo[i].data->time_eat);
        i++;
    }
}

void	round_think(t_philo *copy_ph)
{
	// copy_ph->data->current_time = get_time() - copy_ph->data->time_to_start;
	print_messange(get_time() - copy_ph->data->time_to_start, copy_ph->num_phil, "if thinking.");
}

void	round_sleep(t_philo *copy_ph)
{
	// copy_ph->start_sleep = get_time() - copy_ph->data->time_to_start;
	print_messange(get_time() - copy_ph->data->time_to_start, copy_ph->num_phil, "is sleeping.");
	ft_usleep(copy_ph->data->time_to_sleep);
	// usleep(copy_ph->data->time_to_sleep * 1000);
}


int	take_forks(t_philo *copy_ph)
{
	if (copy_ph->left_fork < copy_ph->right_fork)
	{
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->left_fork]);
		print_messange(get_time() - copy_ph->data->time_to_start, copy_ph->num_phil, "has taken a fork.");
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->right_fork]);
	}
	else if (copy_ph->left_fork > copy_ph->right_fork)
	{
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->right_fork]);
		print_messange(get_time() - copy_ph->data->time_to_start, copy_ph->num_phil, "has taken a fork.");
		pthread_mutex_lock(&copy_ph->data->forks[copy_ph->left_fork]);
	}
	else // случай с одним философом
	{
		return (-1);
	}
	return (0);
}

void	poot_forks(t_philo *copy_ph)
{
	if (copy_ph->left_fork > copy_ph->right_fork)
	{
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->left_fork]);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->right_fork]);
	}
	else if (copy_ph->left_fork < copy_ph->right_fork)
	{
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->right_fork]);
		pthread_mutex_unlock(&copy_ph->data->forks[copy_ph->left_fork]);
	}
}

void	round_eat(t_philo *copy_ph)
{
	// проверка на смерть
	int		i;
	
	i = copy_ph->data->time_to_eat * 1000 / 500;
	pthread_mutex_lock(&copy_ph->data->time_eat);
	copy_ph->start_eat = get_time() - copy_ph->data->time_to_start; //mutex на время
	pthread_mutex_unlock(&copy_ph->data->time_eat);
	print_messange(get_time() - copy_ph->data->time_to_start, copy_ph->num_phil, "is eating.");
	// usleep(copy_ph->data->time_to_eat * 1000);
	ft_usleep(copy_ph->data->time_to_eat);
	if (copy_ph->num_eat++ == INT_MAX)
		copy_ph->num_eat = 0;
}

void *round_life(void *philo)
{
	t_philo *copy_ph;
	
	copy_ph = (t_philo *)philo;
	while (copy_ph->num_eat < copy_ph->data->number_of_philo_eat)
	{
		if (take_forks(copy_ph))
			break ;
		round_eat(copy_ph);
		poot_forks(copy_ph);
		round_sleep(copy_ph);
		round_think(copy_ph);
	}
	pthread_mutex_lock(&copy_ph->data->time_eat);
	copy_ph->data->who_is_eat++;
	pthread_mutex_unlock(&copy_ph->data->time_eat);
	return (NULL);
}

int start_play(t_info *info)
{
	int i;

	i = 0; //time_to_start = get_time()
	info->time_to_start = get_time();
	while (i < info->number_philo)
	{
		if ((pthread_create(&info->philo[i].tread, NULL, &round_life, (void *)(&info->philo[i]))) != 0)
			return (1);
		usleep(100); //500
		i++;
	}
	return (0);
}

void init_phill(t_info *info, int i) // инициализируем структуру каждого философа
{
	info->philo[i].num_phil = i + 1;
	info->philo[i].i = i;
	info->philo[i].left_fork = (i + info->number_philo - 1) % info->number_philo;
	info->philo[i].right_fork = i;
	// printf("%d, %d, %d\n", info->philo[i].num_phil, info->philo[i].left_fork, info->philo[i].right_fork);
	info->philo[i].num_eat = 0;
	info->philo[i].data = info;
	info->philo[i].start_eat = 0;
	pthread_mutex_init(&info->philo[i].data->time_eat, NULL);
}

int before_a_game(t_info *info) // подготовка к началу "голодных игр" плодим необходимое количество структур под каждого философа и узнаем время начала.
{
	int i;
	
	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_philo);
	if (!info->philo)
		return (1);
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->number_philo); //free(info->philo)
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
	return (0);
}

int init_struct(t_info *info, int argc, char **argv) // инициализация структур, присвоение переданных данных.
{
	info->number_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->number_of_philo_eat = INT_MAX;
	info->who_is_eat = 0;
	if (argc == 6)
		info->number_of_philo_eat = ft_atoi(argv[5]);
	if (!(info->number_philo > 0 && info->number_philo <= 200))
		return (1);
	if (info->time_to_die < 0 || info->time_to_eat < 0 
		|| info->time_to_sleep < 0 || info->number_of_philo_eat < -1) //можно не меньше 60 сек
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