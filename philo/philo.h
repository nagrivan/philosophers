/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:11:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/12 20:22:36 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

# define DELAY	500

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t	fork;
};

struct s_philo
{
	int 			num_phil; //номер философа от 1
	int 			i; // скорее всего не нужна
	int				left_fork; // левая вилка
	int				right_fork; // правая вилка
	int				num_eat; // сколько философ пожрал
	time_t			start_eat; // время начала жратвы
	time_t			start_sleep; // время начала сна
	pthread_t		tread;
	struct s_info	*data;
	t_fork			**forks; //ссылка на массив вилок
	// int i_all;
};

struct s_info
{
	int				who_is_eat;
	int				number_philo; // количество философов
	int				number_of_philo_eat; //
	time_t			time_to_die; // время умирать
	time_t			time_to_sleep; // время на сон
	time_t			time_to_eat; // время на еду
	time_t			time_to_start; // время начала
	time_t			current_time; // текущее время
	t_philo			*philo;
	pthread_mutex_t	time_eat;
	// pthread_mutex_t print_mess; // бронь на вывод сообщения
};

void 	*round_life(t_philo *philo);
int		main(int argc, char **argv);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void 	ft_usleep(time_t time);
time_t  get_time(void);
void	print_errors(int error);
void	print_messange(time_t time, int num_phil, char *text);
void	ft_free(t_info *info);

#endif
