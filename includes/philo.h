/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:32 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/02 16:50:59 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LLONG_MIN -9223372036854775807
# define LLONG_MAX 9223372036854775807
# include <sys/time.h>

typedef struct s_info
{
	int	nop;
	int	ttd;
	int	tte;
	int	tts;
	int	notepme;
}				t_info;

typedef struct s_status
{
	int eating;
}				t_status;

typedef struct s_philos
{
	int				pid;
	pthread_t		ph;
	pthread_t		obsrvs;
	int				*l_f;
	int				r_f;
	int				alive;
	pthread_mutex_t	write;
	int				is_eating;
	int				n_of_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	eating;
	long long		starting_time;
	long long		start_eating;
	t_info			info;
	//int				r_f;///
	//int				l_f;///
}				t_philos;

int				ft_atoi(const char *str);
long long int	ft_atol(const char *str);
void			*routine(void *philo);
void			*observer(void *philo);
long long		get_time_in_ms(void);

#endif
