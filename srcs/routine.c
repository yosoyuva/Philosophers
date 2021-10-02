/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:25:43 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/02 17:15:02 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	p_status(t_philos *philo, int pid, char *str))
{
	pthread_mutex_lock(&philo->write);
	printf("%lld %d %s", get_time_in_ms() - philo->starting_time, pid, str);
	if (string[0] != 'd')
		pthread_mutex_unlock(&philo->write);
}

int		routine_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	p_status(philo, philo->pid, "taken left fork\n");
	pthread_mutex_lock(&philo->din_table->forks[philo->rf]);
	p_status(philo, philo->pid, "taken right fork\n");
	pthread_mutex_lock(&philo->eating);
	p_status(philo, philo->pid, "is eating\n");
	philo->start_eating = get_time_in_ms();
	philo->is_eating = 1;
	//usleep(philo->info.tte * 1000 - 16000);
	while (ft_time_in_ms() - philo->start_eating < philo->info.tte)
		continue ;
	philo->n_of_meal++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return ;
}

int		routine_sleep(t_philos *philo)
{

}

int		routine_think(t_philos *philo)
{

}

void	*routine(void *philo)
{
	t_philos	r_philo;

	r_philo = *(t_philos *)philo;
	//pthread_mutex_lock(&(r_philo.mutex));
	/*  CODE   */
	while (r_philo.alive)
	{
		routine_eat(&r_philo);
		routine_sleep(&r_philo);
		routine_think(&r_philo);
	//printf("\nInside routine philo number %d, righ fork = %d, and left = %d\n", r_philo.pid, r_philo.r_f, *(r_philo.l_f));
	}
	/* END OF CODE */
	//pthread_mutex_unlock(&(r_philo.mutex));
	return (NULL);
}

void	*observer(void *philo)
{
	t_philos	r_philo;

	r_philo = *(t_philos *)philo;
	//pthread_mutex_lock(&(r_philo.mutex));
	/*  CODE   */
	while (r_philo.alive)
	{
		if (1 == 2)
			r_philo.alive = 0;
		if (1 == 2)
			r_philo.alive = 0;
	}
	/* END OF CODE */
	//pthread_mutex_unlock(&(r_philo.mutex));
	return (NULL);
}
