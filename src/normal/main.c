/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:44:28 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/07 12:44:29 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

static void	print_usage(void)
{
	write(2, "Usage: ./philo number_of_philosophers time_to_die", 50);
	write(2, " time_to_eat ", 14);
	write(2, "time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 59);
	exit(0);
}

static void	init_options(t_options *options, int ac, char **av)
{
	options->philo_count = ft_atoi(av[1]);
	if (options->philo_count <= 0)
		print_err_exit("philo count must be a positive number");
	options->time_to_die = ft_atoi(av[2]);
	if (options->time_to_die <= 0)
		print_err_exit("time to die must be a positive number");
	options->time_to_eat = ft_atoi(av[3]);
	if (options->time_to_eat <= 0)
		print_err_exit("time to eat must be a positive number");
	options->time_to_sleep = ft_atoi(av[4]);
	if (options->time_to_sleep <= 0)
		print_err_exit("time to sleep must be a positive number");
	options->nb_iter = 0;
	if (ac == 5)
		return ;
	if (ac == 6)
		options->nb_iter = ft_atoi(av[5]);
	if (options->nb_iter <= 0)
		print_err_exit("number of times eating should be a positive number");
}

int	main(int ac, char **av)
{
	t_options	options;
	t_philo		*philos;
	int			i;

	if (5 <= ac && ac <= 6)
		init_options(&options, ac, av);
	else
		print_usage();
	philos = init_philos(&options);
	i = 0;
	options.running = 1;
	pthread_mutex_init(&options.running_m, NULL);
	while (i < options.philo_count)
	{
		pthread_create(&(philos[i].thread),
			NULL, philo_routine, (void *)&philos[i]);
		++i;
	}
	philo_watcher(philos);
	destruct_philos(philos, options.philo_count);
}
