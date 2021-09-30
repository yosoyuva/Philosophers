/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:32 by ymehdi            #+#    #+#             */
/*   Updated: 2021/09/30 18:53:05 by ymehdi           ###   ########.fr       */
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
	int	ttt;
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
	int				*l_f;
	int				r_f;
	pthread_mutex_t	mutex;
	//int				r_f;///
	//int				l_f;///
}				t_philos;

int				ft_atoi(const char *str);
long long int	ft_atol(const char *str);

#endif
