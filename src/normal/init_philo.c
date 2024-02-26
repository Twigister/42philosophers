/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:04:41 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/22 17:04:42 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

static void	new_philo(pthread_mutex_t **forks, int number,
	t_philo *dest, t_options *options)
{
	dest->lfork = forks[0];
	dest->rfork = forks[1];
	dest->options = options;
	dest->number = number;
	dest->last_ate_stamp = 0;
	printf("Philo %d created with %p %p\n", number, forks[0], forks[1]);
}

static void	swap_mutex_ptr(pthread_mutex_t **a, pthread_mutex_t **b)
{
	pthread_mutex_t	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// On crée notre propre fonction pour pouvoir free en cas d'erreur
static void	mutex_creator(t_philo *list, int index, pthread_mutex_t **dest)
{
	int				i;
	pthread_mutex_t	*tmp;

	tmp = malloc(sizeof(pthread_mutex_t));
	if (tmp && pthread_mutex_init(tmp, NULL) == 0)
		*dest = tmp;
	else
	{
		i = 0;
		free(tmp);
		free(*dest);
		while (i < index)
		{
			if (list[i].lfork)
			{
				pthread_mutex_destroy(list[i].lfork);
				free(list[i].lfork);
			}
			++i;
		}
		free(list[i].rfork);
		free(list);
		print_err_exit("mutex initialisation failed");
	}
}

// Gestion d'erreur création de mutex a réaliser
static void	fill_philo_tab(t_options *options, t_philo *philos)
{
	int				i;
	pthread_mutex_t	*fst;
	pthread_mutex_t	*forks[2];

	i = 1;
	fst = NULL;
	forks[1] = NULL;
	mutex_creator(philos, 0, &fst);
	forks[0] = fst;
	if (options->philo_count != 1)
		mutex_creator(philos, 0, &forks[1]);
	else
		forks[1] = fst;
	new_philo(forks, 1, philos, options);
	while (i < options->philo_count - 1)
	{
		swap_mutex_ptr(&forks[0], &forks[1]);
		mutex_creator(philos, i, &forks[1]);
		new_philo(forks, i + 1, philos + i, options);
		++i;
	}
	forks[0] = forks[1];
	forks[1] = fst;
	if (options->philo_count > 1)
		new_philo(forks, i + 1, philos + i, options);
}

t_philo	*init_philos(t_options *options)
{
	t_philo			*res;
	struct timeval	tv;

	if (pthread_mutex_init(&options->counter.m, NULL) != 0)
		print_err_exit("Thread creation failed");
	options->counter.count = 0;
	if (gettimeofday(&tv, NULL) == -1)
	{
		perror("philo");
		pthread_mutex_destroy(&options->counter.m);
		exit(1);
	}
	options->start_stamp = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	res = malloc(sizeof(t_philo) * options->philo_count);
	if (!res)
		print_err_exit("malloc failed");
	ft_bzero(res, sizeof(t_philo) * options->philo_count);
	fill_philo_tab(options, res);
	return (res);
}
