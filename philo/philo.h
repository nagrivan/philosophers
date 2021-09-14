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

# define DELAY			500

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

struct s_philo
{
	int 				num_phil; //номер философа от 1
	int 				i; // скорее всего не нужна
	int					first_fork; // одна вилка вилка
	int					second_fork; // другая вилка вилка
	int					num_eat; // сколько философ пожрал
	time_t				start_eat; // время начала жратвы
	pthread_t			tread;
	struct s_info		*data;
	pthread_mutex_t		**forks; //ссылка на массив вилок
	// int i_all;
};

struct s_info
{
	int					who_is_eat;
	int					number_philo; // количество философов
	int					number_of_philo_eat; //
	time_t				time_to_die; // время умирать
	time_t				time_to_sleep; // время на сон
	time_t				time_to_eat; // время на еду
	time_t				time_to_start; // время начала
	t_philo				*philo;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		print;
	// pthread_mutex_t print_mess; // бронь на вывод сообщения
};

int		main(int argc, char **argv);
void	print_errors(int error);
int 	init_struct(t_info *info, int argc, char **argv);
int 	before_a_game(t_info *info);
void	ft_free(t_info *info);
void	print_errors(int error);
int		start_play(t_info *info);
time_t  get_time(time_t start);
void 	*round_life(t_philo *philo);
int		take_forks(t_philo *philo);
int		round_eat(t_philo *philo);
void	put_forks(t_philo *philo);
int		round_sleep(t_philo *philo);
void	who_is_died(t_info *info);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void 	ft_usleep(time_t time);
void	print_messange(pthread_mutex_t *print, time_t time, int num_phil, char *text);

#endif
