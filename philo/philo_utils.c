/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagrivan <nagrivan@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:08:32 by nagrivan          #+#    #+#             */
/*   Updated: 2021/09/05 20:15:46 by nagrivan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_errors(int error)
{
	if (error == 0)
		printf("%s\n", "Invalid number arguments");
	if (error == 1)
		printf("%s\n", "Invalid arguments");
	if (error == 2)
		printf("%s\n", "Invalid malloc");
	if (error == 3)
		printf("%s\n", "Invalid tread");
	printf("I refuse to work like this!\n");
}

void	print_messange(time_t time, int num_phil, char *text)
{
	printf("| %ld | %d |   %s|\n", time, num_phil, text);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)malloc(count * size);
	if (!(str))
		return (NULL);
	while (i < (count * size))
	{
		*(str + i) = '\0';
		++i;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					res;

	i = 0;
	res = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (str[i] != '\0')
		return (-1);
	return (res);
}

void ft_usleep(int time)
{
	while (time)
	{
		usleep(100);
		time--;
	}
}

time_t  get_time(void)
{
    static struct timeval   time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * (time_t)1000) + time.tv_usec / 1000);;
}
