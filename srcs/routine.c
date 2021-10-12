/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 12:25:43 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/12 16:35:20 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	routine_eat(t_ph *phil)
{
	if (phil->info.nop == 1)
		return (0);
	pthread_mutex_lock(&phil->philo->forks[phil->r_f]);
	p_status(phil, phil->pid, "Has taken a fork right\n");
	pthread_mutex_lock(&phil->philo->forks[phil->l_f]);
	p_status(phil, phil->pid, "Has taken a fork left\n");
	pthread_mutex_lock(&phil->eating);
	p_status(phil, phil->pid, "is eating\n");
	phil->start_eating = get_time_in_ms();
	phil->is_eating = 1;
	usleep(phil->info.tte * 1000 - 16000);
	while (get_time_in_ms() - phil->start_eating < phil->info.tte)
		continue ;
	phil->n_of_meal++;
	phil->is_eating = 0;
	pthread_mutex_unlock(&phil->eating);
	pthread_mutex_unlock(&phil->philo->forks[phil->r_f]);
	pthread_mutex_unlock(&phil->philo->forks[phil->l_f]);
	return (0);
}

int	routine_sleep(t_ph *philo)
{
	long long	time;

	if (philo->info.nop == 1)
		return (0);
	p_status(philo, philo->pid, "is sleeping\n");
	time = get_time_in_ms();
	usleep(philo->info.tts * 1000 - 16000);
	while (get_time_in_ms() - time < philo->info.tts)
		continue ;
	return (0);
}

int	routine_think(t_ph *philo)
{
	if (philo->info.nop == 1)
		return (0);
	p_status(philo, philo->pid, "is thinking\n");
	return (0);
}

void	*routine(void *philo)
{
	t_ph	*r_philo;
	int i= 0;

	r_philo = (t_ph *)philo;
	while (r_philo->philo->alive/* || r_philo->end != 0*/)
	{
	//	fprintf(stderr, "start loop n%d in philo n%d, r_philo->philo->alive = %d\n", i, r_philo->pid, r_philo->philo->alive);
		if (r_philo->end == 0)
			r_philo->philo->alive = 0;
		routine_eat(r_philo);
		//fprintf(stderr, "eat routine for p%d done\n", r_philo->pid);
		routine_sleep(r_philo);
		//fprintf(stderr, "sleep routine for p%d done\n", r_philo->pid);
		routine_think(r_philo);
		//fprintf(stderr, "think routine for p%d done\n", r_philo->pid);
	//	fprintf(stderr, "end loop n%d\n", i);
		i++;
		usleep(100);
		if (r_philo->end == 0)
			r_philo->philo->alive = 0;
	}
	return (NULL);
}

void	*observer(void *r_philo)
{
	t_ph	*phil;

	phil = (t_ph *)r_philo;
	while (phil->philo->alive)
	{
		if (!phil->is_eating
			&& get_time_in_ms() - phil->start_eating >= phil->info.ttd)
		{
			pthread_mutex_lock(&phil->eating);
			if (phil->philo->alive == 0)
			{
				pthread_mutex_unlock(&phil->eating);
				return (NULL);
			}
			p_status(phil, phil->pid, "died\n");
			phil->philo->alive = 0;
			pthread_mutex_unlock(&phil->eating);
		}
		if ((phil->n_of_meal == phil->info.notepme) && (phil->cdt == 1))
		{
			phil->cdt = 0;
			phil->philo->stop++;
		}
		if (phil->philo->stop == phil->info.nop)
			phil->philo->alive = 0;
		usleep(100);
	}
	phil->end = 0;
	pthread_mutex_unlock(&phil->philo->write);
	return (NULL);
}
