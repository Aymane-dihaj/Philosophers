/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:02:49 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/03 16:30:20 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_philo{
	int					last_meal_time;
	int					meals;
	int					index;
	pthread_t			philo_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_var		*var;
}	t_philo;

typedef struct s_var{
	int					time2die;
	int					time2eat;
	int					time2sleep;
	int					is_dead;
	int					max_meals;
	unsigned long		start_time;
	int					count_philos;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		printing;
	pthread_mutex_t		meal;
	pthread_mutex_t		dead;
}	t_var;

int				ft_atoi(char *str);
int				is_int(char *str);
int				load(t_var *var);
int				start_threads(t_var *var);
unsigned long	get_time(void);
int				init_resources(t_var *var);
void			philo_speak(char *sms, int index, t_var *var, int flag);
void			philo_eat(t_philo *philo);
void			stop_philos_life(t_var *var);
void			print_death(int index, t_var *var, char *sms);

#endif