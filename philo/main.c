/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adihaj <adihaj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:02:40 by adihaj            #+#    #+#             */
/*   Updated: 2023/06/07 20:49:25 by adihaj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

int	argument_checker(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_int(argv[i]))
			return (1);
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	load_var(t_var *var, char **argv, int ac)
{
	var->is_dead = 0;
	var->count_philos = ft_atoi(argv[1]);
	var->time2die = ft_atoi(argv[2]);
	var->time2eat = ft_atoi(argv[3]);
	var->time2sleep = ft_atoi(argv[4]);
	if (ac == 6)
	{
		var->max_meals = ft_atoi(argv[5]);
		if (var->max_meals == 0)
			return (1);
	}
	else
		var->max_meals = 0;
	if (var->count_philos <= 0 || var->max_meals < 0
		|| var->time2die <= 0 || var->time2eat <= 0
		|| var->time2sleep <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc > 6 || argc < 5)
		return (print_error("Wrong number of agruments"));
	if (argument_checker(argv, argc))
		return (print_error("Wrong parameters"));
	if (load_var(&var, argv, argc))
		return (print_error("Wrong parameters"));
	if (init_resources(&var))
		return (print_error("Cannot load resources"));
	if (start_threads(&var))
		return (print_error("cannot start threads"));
}
