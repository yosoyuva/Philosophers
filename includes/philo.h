/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:00:32 by ymehdi            #+#    #+#             */
/*   Updated: 2021/10/12 11:45:41 by ymehdi           ###   ########.fr       */
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

struct	s_philos;

typedef struct s_ph
{
	int				pid;
	pthread_t		ph_thread;
	int				l_f;
	int				r_f;
	int				is_eating;
	int				n_of_meal;
	long long		start_eating;
	pthread_mutex_t	eating;
	pthread_t		obsrvs;
	t_info			info;
	struct s_philos	*philo;
	int				end;
	int				cdt;
}				t_ph;

typedef struct s_philos
{
	t_ph			*ph;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	int				alive;
	int				stop;
	long long		starting_time;
	t_info			info;
}				t_philos;

int				ft_atoi(const char *str);
long long int	ft_atol(const char *str);
void			*routine(void *philo);
void			*observer(void *philo);
long long		get_time_in_ms(void);
void			p_status(t_ph *phil, int pid, char *str);
int				check_if_num(char *str);
int				check_if_arg_valid(char **argv, int argc);
t_philos		*ft_init(char **argv, int argc, t_philos *philo);
void			*ft_memalloc(size_t size);

#endif
