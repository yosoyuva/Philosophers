/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:46 by ymehdi            #+#    #+#             */
/*   Updated: 2021/09/30 22:19:54 by ymehdi           ###   ########.fr       */
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
	int	i;

	i = 0;
	free(philo);
	philo = (t_philos *)malloc(sizeof(t_philos) * (info->nop));
	if (philo == NULL)
	{
		printf("Error while mallocing th\n");
		return (-1);
	}
	//philo[info->nop] = '\0';
/*	while (i < info->nop)
	{
		philo[i]->mutex = malloc(sizeof(pthread_mutex_t) * (info->nop + 1));
		if (philo[i]->mutex == NULL)
		{
			printf("Error while mallocing mutex\n");
			free(philo);
			return (-1);
		}
		i++;
	}*/
	//fprintf(stderr, "phio\n");
	philo[1].r_f = 75;
	info->notepme = 5;
	fprintf(stderr, "philo[1]->r_f = %d, info->notepme = %d\n", philo[1].r_f, info->notepme);

	//thread->r_f = 0;///
	//thread->l_f = 0;///
	return (1);
}

int	ft_get_infos(t_info *info, char **argv, int argc)
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

void	*routine(void *philo)
{
	t_philos	r_philo;

	r_philo = *(t_philos *)philo;
	pthread_mutex_lock(&(r_philo.mutex));
	/*  CODE   */
//	while (check_if_still_alive)
//	{
	printf("\nInside routine philo number %d\n", r_philo.pid);
//	}
	/* END OF CODE */
	pthread_mutex_unlock(&(r_philo.mutex));
	return (NULL);
}

void	ft_init(t_philos **philo, t_info *info)
{
	int	i;

	i = 0;
	fprintf(stderr, "20\n");
	while (i < info->nop)
	{
		//fprintf(stderr, "20%d\n", i);
		philo[i]->r_f = 0;
		//fprintf(stderr, "20%d1\n", i);
		if (i == info->nop - 1)
			philo[i]->l_f = &(philo[0]->r_f);
		else
			philo[i]->l_f = &(philo[i + 1]->r_f);
		//fprintf(stderr, "20%d2\n", i);
		philo[i]->pid = i + 1;
	//	fprintf(stderr, "20%d3\n", i);
		i++;
	}
	fprintf(stderr, "21\n");
	// Check si ca fonctionne
	i = 0;
	while (i < info->nop)
	{
		printf("For philo number %d right fork is = %d, and left = %p ", philo[i]->pid, philo[i]->r_f, philo[i]->l_f);
		i++;
	}
	fprintf(stderr, "22\n");
}

int	main(int argc, char **argv)
{
	t_philos	*philo;
	t_info		info;
	int i = 0;
	//int *j;

	philo = (t_philos *)malloc(sizeof(t_philos) * 1);
	if (argc < 5 || argc > 6)
	{
		printf("Philo needs 5 args with the fifth in option\n");
		return (0);
	}
	if (ft_get_infos(&info, argv, argc) == -1)
		return (0);
	fprintf(stderr, "1\n");
	if (ft_thread_mutex_init(&info, philo) == -1)
		return (0);

	fprintf(stderr, "2 et philo[1].r_f = %d, info.notepme = %d\n", philo[1].r_f, info.notepme);
	ft_init(&philo, &info);
	fprintf(stderr, "3\n");
	while (i < info.nop)
	{
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
	fprintf(stderr, "3\n");
	i = 0;
	while (i < info.nop)
	{
		pthread_create(&philo[i].ph, NULL, &routine, philo + i);
		i++;
	}
	fprintf(stderr, "3\n");
	i = 0;
	while (i < info.nop)
	{
		pthread_join(philo[i].ph, NULL);
		i++;
	}
	fprintf(stderr, "3\n");



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
	free(philo);
	return (0);
}
