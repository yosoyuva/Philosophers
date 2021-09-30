/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:46 by ymehdi            #+#    #+#             */
/*   Updated: 2021/09/30 02:40:48 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	ft_thread_mutex_init(t_info *info, t_philos *philo)
{
	philo = malloc(sizeof(t_philos) * (info->nop + 1));
	if (philo == NULL)
	{
		printf("Error while mallocing th\n");
		return (-1);
	}
	philo->mutex = malloc(sizeof(pthread_mutex_t) * (info->nop + 1));
	if (thread->mutex == NULL)
	{
		printf("Error while mallocing mutex\n");
		free(philo->ph);
		return (-1);
	}
	//thread->r_f = 0;///
	//thread->l_f = 0;///
	return (1);
}

int	ft_get_args(t_info *info, char **argv, int argc)
{
	if (check_if_arg_valid(argv, argc) == -1)
	{
		printf("Non valid args\n");
		return (-1);
	}
	info->nop = ft_atoi(argv[1]);
	info->ttd =ft_atoi(argv[2]);
	info->ttt = ft_atoi(argv[3]);
	info->tts =ft_atoi(argv[4]);
	if (argc == 6)
		info->notepme = ft_atoi(argv[5]);
	return (1);
}

void	*routine(void *thread)
{
	t_thread	r_thread;

	r_thread = *(t_thread *)thread;
	pthread_mutex_lock(r_thread.mutex);
	/*  CODE   */
	while (check_if_still_alive)
	{

	}
	pthread_mutex_unlock(r_thread.mutex);
	return (NULL);
}

void	ft_init(t_philos *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nop)
	{
		philo[i]->l_f = 0;
		if (i == info->nop - 1)
			philo[i]->r_f = *(philo[0]->l_f);
		else
			philo[i]->r_f = *(philo[i + 1]->l_f);
		philo[i]->pid = i + 1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philos	*philo;
	t_info		info;
	int i = 0;
	//int *j;

	//th = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Philo needs 5 args with the fifth in option\n");
		return (0);
	}
	if (ft_get_args(&info, argv, argc) == -1)
		return (0);
	if (ft_thread_mutex_init(&info, philo) == -1)
		return (0);
	ft_init(philo, &info);
	while (i < info.nop)
	{
		pthread_mutex_init(&philo.mutex[i], NULL);
		i++;
	}
	i = 0;
	while (i < info.nop)
	{
		pthread_create(&philo.ph[i], NULL, &routine, &philo);
		i++;
	}
	i = 0;
	while (i < info.nop)
	{
		pthread_join(philo.ph[i], NULL);
		i++;
	}



	/*while (i < ft_atoi(argv[1]))
	{
		j = malloc(sizeof(int));
		*j = i;
		//printf("sur le point de rentre dans thread num%d\n", j);
		pthread_create(&th[i], NULL, &routines, j);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(th[i], NULL);
		i++;
	}*/
	free(philo.ph);
	return (0);
}
