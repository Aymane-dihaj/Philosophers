/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:18:09 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/07 20:49:25 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	load_mutex(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->count_philos)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&var->meal, NULL))
		return (1);
	if (pthread_mutex_init(&var->printing, NULL))
		return (1);
	if (pthread_mutex_init(&var->dead, NULL))
		return (1);
	return (0);
}

int	load_philos(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->count_philos)
	{
		var->philos[i].meals = 0;
		var->philos[i].last_meal_time = 0;
		var->philos[i].var = var;
		var->philos[i].index = i + 1;
		var->philos[i].left_fork = &var->forks[i];
		if (i < var->count_philos - 1)
			var->philos[i].right_fork = &var->forks[i + 1];
		else
			var->philos[i].right_fork = &var->forks[0];
		i++;
	}
	return (0);
}

int	init_resources(t_var *var)
{
	int	i;

	i = 0;
	var->philos = malloc(sizeof(t_philo) * var->count_philos);
	if (!var->philos)
		return (1);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->count_philos);
	if (!var->forks)
		return (free(var->philos), 1);
	if (load_mutex(var))
		return (free(var->philos), free(var->forks), 1);
	if (load_philos(var))
		return (1);
	return (0);
}
