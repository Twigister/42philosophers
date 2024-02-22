/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:10:50 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/22 17:10:51 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

static void	philo_eat(t_philo *self)
{
	if (self->number % 2)
	{
		pthread_mutex_lock(self->lfork);
		printf("%ld %d has taken a fork!\n",
			get_timestamp(self->options->start_stamp),
			self->number);
		pthread_mutex_lock(self->rfork);
	}
	else
	{
		pthread_mutex_lock(self->rfork);
		printf("%ld %d has taken a fork!\n",
			get_timestamp(self->options->start_stamp),
			self->number);
		pthread_mutex_lock(self->lfork);
	}
	printf("%ld %d has taken a fork!\n",
		get_timestamp(self->options->start_stamp),
		self->number);
	printf("%ld %d is eating\n",
		get_timestamp(self->options->start_stamp), self->number);
	usleep(self->options->time_to_eat * 1000);
	pthread_mutex_unlock(self->lfork);
	pthread_mutex_unlock(self->rfork);
	self->last_ate_stamp = get_timestamp(self->options->start_stamp);
}

void	*philo_routine(void	*data)
{
	t_philo	*self;
	int		ate_count;

	self = (t_philo *)data;
	ate_count = 0;
	if (self->number % 2)
		usleep(1000);
	while (1)
	{
		printf("%ld %d is thinking\n", get_timestamp(self->options->start_stamp),
			self->number);
		usleep(1000);
		philo_eat(self);
		++ate_count;
		if (ate_count == self->options->nb_iter)
		{
			pthread_mutex_lock(&self->options->counter.m);
			self->options->counter.count += 1;
			pthread_mutex_unlock(&self->options->counter.m);
		}
		printf("%ld %d is sleeping\n", get_timestamp(self->options->start_stamp),
			self->number);
		usleep(self->options->time_to_sleep * 1000);
	}
	return (NULL);
}

void	philo_watcher(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&philos->options->counter.m);
		if (philos->options->counter.count == philos->options->philo_count)
			break ;
		pthread_mutex_unlock(&philos->options->counter.m);
		while (i < philos->options->philo_count)
		{
			printf("%d + %d = %d < %ld\n", philos[i].last_ate_stamp, philos->options->time_to_die,
			philos[i].last_ate_stamp + philos->options->time_to_die, get_timestamp(philos->options->start_stamp));

			if (philos[i].last_ate_stamp + philos->options->time_to_die
				< get_timestamp(philos->options->start_stamp))
					break ;
			++i;
		}
	}
}
