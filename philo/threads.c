/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:14:12 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/07 20:49:25 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *params)
{
	t_philo		*philo;
	t_var		*var;

	philo = (t_philo *)params;
	var = philo->var;
	if ((philo->index % 2) && var->count_philos > 1)
		usleep(var->time2eat);
	while (1)
	{
		pthread_mutex_lock(&var->dead);
		if (var->is_dead)
		{
			pthread_mutex_unlock(&var->dead);
			break ;
		}
		pthread_mutex_unlock(&var->dead);
		philo_eat(philo);
		philo_speak("is sleeping", philo->index, var, 1);
		usleep(var->time2sleep * 1000);
		philo_speak("is thinking", philo->index, var, 1);
	}
	return (NULL);
}

void	check_max_meals(t_var *var)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (i++ < var->count_philos)
	{
		pthread_mutex_lock(&var->meal);
		if (var->philos[i].meals >= var->max_meals)
			count++;
		pthread_mutex_unlock(&var->meal);
	}
	if (count == var->count_philos)
	{
		pthread_mutex_lock(&var->dead);
		var->is_dead = 1;
		pthread_mutex_unlock(&var->dead);
	}
}

void	check_death(t_var *var)
{
	int	i;

	while (!var->is_dead)
	{
		i = 0;
		while (i < var->count_philos && !var->is_dead)
		{
			pthread_mutex_lock(&var->meal);
			if ((int)(get_time() - var->start_time
				- var->philos[i].last_meal_time) >= var->time2die)
				print_death(i + 1, var, "is died");
			pthread_mutex_unlock(&var->meal);
			usleep(100);
			i++;
		}
		if (var->max_meals != 0 && !var->is_dead)
			check_max_meals(var);
	}
}

int	start_threads(t_var *var)
{
	int			i;
	t_philo		*philo;

	i = -1;
	philo = var->philos;
	var->start_time = get_time();
	while (++i < var->count_philos)
	{
		if (pthread_create(&philo[i].philo_id, NULL, routine, &philo[i]))
			return (1);
	}
	check_death(var);
	stop_philos_life(var);
	return (0);
}
