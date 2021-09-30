/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 17:59:30 by ymehdi            #+#    #+#             */
/*   Updated: 2021/09/28 18:56:17 by ymehdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_iswhite_space(int *i, const char *str)
{
	while (str[*i] == ' ' || str[*i] == '\f'
		|| str[*i] == '\n' || str[*i] == '\r'
		|| str[*i] == '\t' || str[*i] == '\v')
		(*i)++;
	return (*i);
}

int	ft_issign(int *i, const char *str, int *sign)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
	return (*i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	res = 0;
	i = ft_iswhite_space(&i, str);
	ft_issign(&i, str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > INT_MAX / 10) || (res == INT_MAX / 10 && str[i] - 48 > 7))
		{
			if (sign == 1)
				return (-1);
			else if (res * sign == INT_MIN / 10 && str[i] - 48 > 7)
				return (INT_MIN);
			else
				return (0);
		}
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

long long int	ft_atol(const char *str)
{
	int				i;
	int				sign;
	long long int	res;

	sign = 1;
	i = 0;
	res = 0;
	i = ft_iswhite_space(&i, str);
	ft_issign(&i, str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((res > LLONG_MAX / 10) || (res == LLONG_MAX / 10 \
			&& str[i] - 48 > 7))
		{
			if (sign == 1)
				return (-1);
			else if (res * sign == LLONG_MIN / 10 && str[i] - 48 > 7)
				return (LLONG_MIN);
			else
				return (0);
		}
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
