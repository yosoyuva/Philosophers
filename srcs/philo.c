/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:46 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/12 11:49:51 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philos	*create_threads_aux(t_philos *philo)
{
	int	i;

	i = 0;
//	int j = 0;
//	while (j < philo->info.nop)
//	{
//		fprintf(stderr, "test inside create_threads, philo->ph[%d].end = %d, philo->ph[%d].pid = %d\n", j, philo->ph[j].end, j, philo->ph[j].pid);
//		j++;
//	}
//	fprintf(stderr, "Inside create_threads_aux Before any creation\n");
	while (i < philo->info.nop)
	{
	//	fprintf(stderr, "Inside philo's creation loop p%d/%d\n", philo->ph[i].pid, philo->info.nop);
		philo->ph[i].start_eating = get_time_in_ms();
		if (pthread_create(&philo->ph[i].ph_thread, NULL, \
			&routine, (void *)&philo->ph[i]) != 0)
		{
			fprintf(stderr, "p%d failed launching\n", philo->ph[i].pid);
			return (NULL);
		}
		usleep(100);
		i++;
	}
//	fprintf(stderr, "Inside create_threads_aux Before creation of observers\n");
	i = 0;
	while (i < philo->info.nop)
	{
		if (pthread_create(&philo->ph[i].obsrvs, NULL, \
			&observer, (void *)&philo->ph[i]) != 0)
		{
			fprintf(stderr, "observer n%d failed launching\n", philo->ph[i].pid);
			return (NULL);
		}
		usleep(100);
		i++;
	}
	//fprintf(stderr, "philos and observers launched\n");
	i = 0;
	while (i < philo->info.nop)
	{
		pthread_join(philo->ph[i].obsrvs, NULL);
		fprintf(stderr, "observer n%d was joined\n", philo->ph[i].pid);
		pthread_join(philo->ph[i].ph_thread, NULL);
		fprintf(stderr, "p%d was joined\n", philo->ph[i].pid);
		i++;
	}
	return (philo);
}

void	create_threads(t_philos *philo)
{
//	int	i;
//	t_philos *tmp;
/*	int i = 0;
	while (i < philo->info.nop)
	{
		fprintf(stderr, "test inside create_threads, philo->ph[%d].end = %d, philo->ph[%d].pid = %d\n", i, philo->ph[i].end, i, philo->ph[i].pid);
		i++;
	}*/
/*	fprintf(stderr, "Inside create_threads Before aux\n");*/
//	tmp = create_threads_aux(philo);
//	free(philo->ph);
//	free(philo->forks);
	create_threads_aux(philo);
//	fprintf(stderr, "create_threads_aux done\n");

//	fprintf(stderr, "after creating and finishing threads\n");
/*	if (philo == NULL)
	{
		free(philo->ph);
		free(philo->forks);
		return ;
	}
	i = 0;
	while (1)
	{
		i = 0;
		while (i < philo->info.nop)
		{
			if (philo->ph[i].end == 0)
			{
				free(philo->ph);
				free(philo->forks);
				return ;
			}
			i++;
		}
		continue ;
	}*/
//	free(philo->ph);
//	free(philo->forks);
	return ;
}

int	main(int argc, char **argv)
{
	t_philos	*philo;
	//t_philos	*tmp;

/*	philo = (t_philos *)malloc(sizeof(t_philos));      */
	philo = ft_memalloc(sizeof(t_philos));
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
	//fprintf(stderr, "Before init\n");
	philo = ft_init(argv, argc, philo);
//	int i = 0;
//	while (i < philo->info.nop)
//	{
//		fprintf(stderr, "test after init, philo->ph[%d].end = %d, philo->ph[%d].pid = %d\n", i, philo->ph[i].end, i, philo->ph[i].pid);
//		i++;
//	}
	if (philo->ph == NULL)
	{
		fprintf(stderr, "ft_init() failed\n");
		return (0);
	}
//	fprintf(stderr, "Before creating threads\n");
	create_threads(philo);
	usleep(1000);
	free(philo->ph);
	free(philo->forks);
	free(philo);
	return (0);
}
