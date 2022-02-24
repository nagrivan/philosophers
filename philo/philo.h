/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:11:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/16 20:32:13 by nagrivan         ###   ########.fr       */
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
	int					num_phil;
	int					first_fork;
	int					second_fork;
	int					num_eat;
	time_t				start_eat;
	pthread_t			tread;
	struct s_info		*data;
	pthread_mutex_t		**forks;
};

struct s_info
{
	int					who_is_eat;
	int					number_philo;
	int					number_of_philo_eat;
	time_t				time_to_die;
	time_t				time_to_sleep;
	time_t				time_to_eat;
	time_t				time_to_start;
	t_philo				*philo;
	pthread_mutex_t		time_eat;
	pthread_mutex_t		print;
};

int		ft_atoi(const char *str);
void	ft_usleep(time_t time);
void	ft_free(t_info *info);
time_t	get_time(time_t start);

size_t	ft_strlen(const char *s);
void	print_errors(int error);
void	print_messange(pthread_mutex_t *print,
			time_t time, int num_phil, char *text);

int		main(int argc, char **argv);
int		preporat_game(t_info *info, int argc, char **argv);
int		before_a_game(t_info *info);
int		start_play(t_info *info);

int		init_struct(t_info *info, int argc, char **argv);
void	init_mut_phil(t_info *info, pthread_mutex_t *forks,
			pthread_mutex_t **forks_pt);
void	init_phill(t_info *info, int i, pthread_mutex_t **forks,
			t_philo *philo);

void	*round_life(t_philo *philo);
int		take_forks(t_philo *philo);
int		round_eat(t_philo *philo);
void	put_forks(t_philo *philo);
int		round_sleep(t_philo *philo);

void	who_is_died(t_info *info);
int		check_die(t_info *info, int i);

#endif
