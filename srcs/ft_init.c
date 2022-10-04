/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:23:36 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/12 17:55:57 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philos	*ft_init_aux(t_philos *philo, char **argv, int argc)
{
	pthread_mutex_init(&philo->write, NULL);
	philo->alive = 1;
	philo->stop = 0;
	philo->starting_time = get_time_in_ms();
	philo->info.nop = ft_atoi(argv[1]);
	philo->info.ttd = ft_atoi(argv[2]);
	philo->info.tte = ft_atoi(argv[3]);
	philo->info.tts = ft_atoi(argv[4]);
	if (argc == 6)
		philo->info.notepme = ft_atoi(argv[5]);
	else
		philo->info.notepme = -1;
	return (philo);
}

t_philos	*ft_init_aux2(t_philos *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo->ph[i].n_of_meal = 0;
		philo->ph[i].is_eating = 0;
		philo->ph[i].r_f = i;
		philo->ph[i].l_f = (i + 1) % philo->info.nop;
		philo->ph[i].pid = i + 1;
		philo->ph[i].info = philo->info;
		philo->ph[i].philo = philo;
		philo->ph[i].end = 1;
		philo->ph[i].cdt = 1;
		pthread_mutex_init(&philo->forks[i], NULL);
		pthread_mutex_init(&philo->ph[i].eating, NULL);
		i++;
	}
	return (philo);
}

t_philos	*ft_init(char **argv, int argc, t_philos *philo)
{
	int			i;

	i = 0;
	philo->ph = ft_memalloc(sizeof(t_ph) * (ft_atoi(argv[1]) + 1));
	if (philo->ph == NULL)
	{
		printf("Error while mallocing ph\n");
		return (philo);
	}
	philo->forks = ft_memalloc(sizeof(pthread_mutex_t) \
		* (ft_atoi(argv[1]) + 1));
	if (philo->forks == NULL)
	{
		printf("Error while mallocing forks\n");
		return (philo);
	}
	philo = ft_init_aux(philo, argv, argc);
	philo = ft_init_aux2(philo, argv);
	return (philo);
}
