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
		usleep(DELAY);
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
		pthread_mutex_unlock(&info->philo[i].data->time_eat);
		if (info->who_is_eat == info->number_philo) //max_int
		{
			printf("| %ld | - | %s |\n", info->current_time, "all are eating");
//			pthread_mutex_unlock(&info->philo[i].data->time_eat);
			return ;
		}
//		pthread_mutex_unlock(&info->philo[i].data->time_eat);
        i++;
    }
}

int	round_sleep(t_philo *philo)
{
	time_t	start_sleep;
	
	start_sleep = get_time() - philo->data->time_to_start;
	if (start_sleep - philo->start_eat > philo->data->time_to_die)
		return (-1);
	else
	{
	print_messange(get_time() - philo->data->time_to_start, philo->num_phil, "is sleeping.");
	ft_usleep(philo->data->time_to_sleep);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->forks[philo->left_fork]);
		print_messange(get_time() - philo->data->time_to_start, philo->num_phil, "has taken a fork.");
		pthread_mutex_lock(philo->forks[philo->right_fork]);
	}
	else if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_lock(philo->forks[philo->right_fork]);
		print_messange(get_time() - philo->data->time_to_start, philo->num_phil, "has taken a fork.");
		pthread_mutex_lock(philo->forks[philo->left_fork]);
	}
	else // случай с одним философом
	{
		return (-1);
	}
	return (0);
}

void	put_forks(t_philo *philo)
{
	if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_unlock(philo->forks[philo->left_fork]);
		pthread_mutex_unlock(philo->forks[philo->right_fork]);
	}
	else if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(philo->forks[philo->right_fork]);
		pthread_mutex_unlock(philo->forks[philo->left_fork]);
	}
}

int	round_eat(t_philo *philo)
{
	time_t	start_eat;
	
	start_eat = get_time() - philo->data->time_to_start;
	if (start_eat - philo->start_eat > philo->data->time_to_die)
		return (-1);
	else
	{
	pthread_mutex_lock(&philo->data->time_eat);
	philo->start_eat = start_eat; //mutex на время
	pthread_mutex_unlock(&philo->data->time_eat);
	}
	print_messange(get_time() - philo->data->time_to_start, philo->num_phil, "is eating.");
	ft_usleep(philo->data->time_to_eat);
	if (philo->num_eat++ == INT_MAX)
		philo->num_eat = 0;
	return (0);
}

void *round_life(t_philo *philo)
{
	while (philo->num_eat < philo->data->number_of_philo_eat)
	{
		if (take_forks(philo))
			break ;
		if (round_eat(philo) == -1)
			break ;
		put_forks(philo);
		if (round_sleep(philo) == -1)
			break ;
		print_messange(get_time() - philo->data->time_to_start, philo->num_phil, "if thinking.");
	}
	pthread_mutex_lock(&philo->data->time_eat);
	philo->data->who_is_eat++;
	pthread_mutex_unlock(&philo->data->time_eat);
	return (NULL);
}

int start_play(t_info *info)
{
	int i;

	i = 0; //time_to_start = get_time()
	info->time_to_start = get_time();
	while (i < info->number_philo)
	{
		if ((pthread_create(&info->philo[i].tread, NULL, (void *)&round_life, &info->philo[i])) != 0)
			return (1);
		usleep(DELAY); //500
		i++;
	}
	return (0);
}

void init_phill(t_info *info, int i, pthread_mutex_t **forks, t_philo *philo) // инициализируем структуру каждого философа
{
	philo->num_phil = i + 1;
	philo->i = i;
	if (i == 0)
	{
		philo->left_fork = info->number_philo - 1;
		philo->right_fork = i;
	}
	else if (i == info->number_philo - 1)
	{
		philo->left_fork = i - 1;
		philo->right_fork = 0;
	}
	else
	{
		philo->left_fork = i - 1;
		philo->right_fork = i;
	}
//	philo->left_fork = (i + info->number_philo - 1) % info->number_philo;
//	philo->right_fork = i;
	philo->num_eat = 0;
	philo->data = info;
	philo->start_eat = 0;
	philo->forks = forks;

	pthread_mutex_init(&info->philo[i].data->time_eat, NULL);
}

int before_a_game(t_info *info) // подготовка к началу "голодных игр" плодим необходимое количество структур под каждого философа и узнаем время начала.
{
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	**forks_pt;
	
	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->number_philo);
	if (!info->philo)
		return (1);
	forks = malloc(sizeof(pthread_mutex_t) * info->number_philo); //free(info->philo)
	if (!forks)
		return (1);
	forks_pt = malloc(sizeof(pthread_mutex_t *) * info->number_philo);
	if (!forks_pt)
		return (1);
	while (i < info->number_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		forks_pt[i] = &forks[i];
		i++;
	}
	i = 0;
	while (i < info->number_philo)
	{
		init_phill(info, i, forks_pt, &info->philo[i]);
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
		ft_free(&info);//FIXME
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
