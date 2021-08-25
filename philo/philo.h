/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:11:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/08/25 04:04:05 by nagrivan         ###   ########.fr       */
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

typedef struct s_info
{
	int number_philo;
	int number_of_philo_eat;
	time_t time_to_die;
	time_t time_to_sleep;
	time_t time_to_eat;
	t_philo *philo
} t_info;

typedef struct s_philo
{
	int num_phil;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	int num_eat;
	time_t start_eat;
	time_t start_sleep;
	pthread_t tread;
	t_info data;
} t_philo;

int main(int argc, char **argv);
int	ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void ft_usleep(int time);
time_t  get_time(void);

#endif