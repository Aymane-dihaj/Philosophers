/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:06:28 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/07 20:49:25 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_speak(char *sms, int index, t_var *var, int flag)
{
	pthread_mutex_lock(&var->printing);
	pthread_mutex_lock(&var->dead);
	if (!var->is_dead)
		printf("%ld philo %d: %s\n", get_time() - var->start_time, index, sms);
	pthread_mutex_unlock(&var->dead);
	if (flag)
		pthread_mutex_unlock(&var->printing);
}

void	print_death(int index, t_var *var, char *sms)
{
	pthread_mutex_lock(&var->printing);
	pthread_mutex_lock(&var->dead);
	if (!var->is_dead)
		printf("%ld philo %d: %s\n", get_time() - var->start_time, index, sms);
	usleep(100);
	var->is_dead = 1;
	pthread_mutex_unlock(&var->dead);
	pthread_mutex_unlock(&var->printing);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_speak("has taken left fork", philo->index, philo->var, 1);
	pthread_mutex_lock(philo->right_fork);
	philo_speak("has taken right fork", philo->index, philo->var, 1);
	pthread_mutex_lock(&philo->var->meal);
	philo_speak("is eating", philo->index, philo->var, 1);
	philo->last_meal_time = get_time() - philo->var->start_time;
	pthread_mutex_unlock(&philo->var->meal);
	usleep(philo->var->time2eat * 1000);
	pthread_mutex_lock(&philo->var->meal);
	philo->meals++;
	pthread_mutex_unlock(&philo->var->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
