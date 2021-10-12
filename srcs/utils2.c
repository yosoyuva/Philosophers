/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:04:57 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/12 14:45:43 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	te;
	long long		ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (ms);
}

void	p_status(t_ph *phil, int pid, char *str)
{
	pthread_mutex_lock(&phil->philo->write);
	if (phil->philo->alive == 0)
	{
		pthread_mutex_unlock(&phil->philo->write);
		return ;
	}
	printf("%lld %d %s", get_time_in_ms() - phil->philo->starting_time, \
			pid, str);
	if (str[0] != 'd')
	{
		pthread_mutex_unlock(&phil->philo->write);
	}
	else
	{
		phil->philo->alive = 0;
		pthread_mutex_unlock(&phil->philo->write);	
	}
}

int	check_if_arg_valid(char **argv, int argc)
{
	long long int	res;
	int				i;

	i = 1;
	while (i < argc - 1)
	{
		if (!check_if_num(argv[i]))
			return (-1);
		res = ft_atol(argv[i]);
		if (res > INT_MAX || res < 0)
			return (-1);
		i++;
	}
	return (1);
}

int	check_if_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
