/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:46 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/02 16:51:08 by ymehdi           ###   ########.fr       */
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



/*int	ft_get_infos(char **argv, int argc)
{
	t_philos	philo;

	info->nop = ft_atoi(argv[1]);
	info->ttd =ft_atoi(argv[2]);
	info->ttt = ft_atoi(argv[3]);
	info->tts =ft_atoi(argv[4]);
	if (argc == 6)
		info->notepme = ft_atoi(argv[5]);
	return (1);
}*/

t_philos	*ft_init(char **argv, int argc)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = (t_philos *)malloc(sizeof(t_philos) * (ft_atoi(argv[1])));
	if (philo == NULL)
	{
		printf("Error while mallocing th\n");
		return (NULL);
	}
	while (i < ft_atoi(argv[1]))
	{
		philo[i].info.nop = ft_atoi(argv[1]);
		philo[i].info.ttd =ft_atoi(argv[2]);
		philo[i].info.tte = ft_atoi(argv[3]);
		philo[i].info.tts =ft_atoi(argv[4]);
		if (argc == 6)
			philo[i].info.notepme = ft_atoi(argv[5]);
		philo[i].alive = 1;
		philo[i].n_of_meal = 0;
		philo[i].r_f = 0;
		if (i == philo[i].info.nop - 1)
			philo[i].l_f = &(philo[0].r_f);
		else
			philo[i].l_f = &(philo[i + 1].r_f);
		philo[i].pid = i + 1;
		i++;
	}
	// Check si ca fonctionne
	i = 0;
	while (i < philo[0].info.nop)
	{
		printf("For philo number %d right fork is = %d, and left = %d (r_f = %p). alive = %d \n", philo[i].pid, philo[i].r_f, *(philo[i].l_f), &(philo[i].r_f), philo[i].alive);
		i++;
	}
	fprintf(stderr, "22\n");
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philos	*philo;
	//t_info		info;
	int i = 0;
	//int *j;

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
	//if (ft_get_infos(&info, argv, argc) == -1)
	//	return (0);
	fprintf(stderr, "1\n");
	//philo = ft_thread_mutex_init(&info);
	philo = ft_init(argv, argc);
	if (philo == NULL)
		return (0);
	fprintf(stderr, "2 et philo[3].r_f = %d, info.notepme = %d\n", philo[3].r_f, philo[0].info.notepme);
	//ft_init(&philo, &info);
	fprintf(stderr, "3\n");
	while (i < philo[0].info.nop)
	{
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].right_fork, NULL);
		i++;
	}
	fprintf(stderr, "3\n");
	i = 0;
	philo[0].starting_time = get_time_in_ms();
	while (i < philo[0].info.nop)
	{
		pthread_create(&philo[i].ph, NULL, &routine, philo + i);
		i++;
	}
	fprintf(stderr, "3\n");
	i = 0;
	while (i < philo[0].info.nop)
	{
		pthread_create(&philo[i].obsrvs, NULL, &observer, philo + i);
		i++;
	}
	/*while (i < info.nop)
	{
		pthread_join(philo[i].ph, NULL);
		i++;
	}*/
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









/*t_philos	*ft_thread_mutex_init(t_info *info)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = (t_philos *)malloc(sizeof(t_philos) * (info->nop));
	if (philo == NULL)
	{
		printf("Error while mallocing th\n");
		return (NULL);
	}*/
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
	//philo[1].r_f = 75;
	//info->notepme = 5;

	//thread->r_f = 0;///
	//thread->l_f = 0;///
//	return (philo);
//}
