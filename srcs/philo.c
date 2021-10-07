/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:46 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/07 23:40:42 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philos	*create_threads_aux(t_philos *philo)
{
	int	i;

	i = 0;
	while (i < philo->info.nop)
	{
		philo->ph[i].start_eating = get_time_in_ms();
		if (pthread_create(&philo->ph[i].ph_thread, NULL, \
			&routine, (void *)&philo->ph[i]) != 0)
			return (NULL);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < philo->info.nop)
	{
		if (pthread_create(&philo->ph[i].obsrvs, NULL, \
			&observer, (void *)&philo->ph[i]) != 0)
			return (NULL);
		usleep(100);
		i++;
	}
	return (philo);
}

void	create_threads(t_philos *philo)
{
	int	i;

	philo = create_threads_aux(philo);
	if (philo == NULL)
		return ;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo->info.nop)
		{
			if (philo->ph[i].end == 0)
				return ;
			i++;
		}
		continue ;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_philos	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Philo needs 5 args with the fifth in option\n");
		return (0);
	}
	if (check_if_arg_valid(argv, argc) == -1)
	{
		printf("Non valid args\n");
		return (-1);
	}
	philo = ft_init(argv, argc);
	if (philo.ph == NULL)
	{
		fprintf(stderr, "ft_init() failed\n");
		return (0);
	}
	create_threads(&philo);
	usleep(1000);
	free(philo.ph);
	free(philo.forks);
	return (0);
}
