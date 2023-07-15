/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:28:27 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/07 20:49:25 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int				sign;
	unsigned long	result;
	int				i;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
				i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - 48);
	}
	if (result > 2147483647 && sign == 1)
		return (-1);
	else if (result > 2147483647 && sign == -1)
		return (-1);
	return (result * sign);
}

int	is_int(char *str)
{
	int				sign;
	int				i;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	stop_philos_life(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->count_philos)
	{
		if (var->count_philos > 1)
			pthread_join(var->philos[i].philo_id, NULL);
		i++;
	}
	i = 0;
	while (i < var->count_philos)
	{
		pthread_mutex_destroy(&var->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&var->meal);
	pthread_mutex_destroy(&var->printing);
	pthread_mutex_destroy(&var->dead);
	free(var->forks);
	free(var->philos);
}
