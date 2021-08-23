/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:11:55 by nagrivan          #+#    #+#             */
/*   Updated: 2021/08/23 18:42:45 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

typedef struct s_info
{
	int number_philo;
	time_t time_to_die;
	time_t time_to_sleep;
	time_t time_to_eat;
} t_info;

typedef struct s_philo
{
	int left_fork;
	int right_fork;
	int number_of_philo_eat;
} t_philo;

int main(int argc, char **argv);
void ft_usleep(int time);

#endif