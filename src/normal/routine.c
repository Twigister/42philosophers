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

static int	philo_action(t_philo *self, const char *text)
{
	int			running;
	suseconds_t	ts;

	pthread_mutex_lock(&self->options->running_m);
	running = self->options->running;
	ts = self->options->running;
	pthread_mutex_unlock(&self->options->running_m);
	if (running)
		printf("%ld %d %s\n", ts, self->number, text);
	else
		return (1);
	return (0);
}

static int	philo_eat(t_philo *self)
{
	if (self->number % 2)
	{
		pthread_mutex_lock(self->lfork);
		if (philo_action(self, "has taken a fork"))
			return (pthread_mutex_unlock(self->lfork), 1);
		pthread_mutex_lock(self->rfork);
	}
	else
	{
		pthread_mutex_lock(self->rfork);
		if (philo_action(self, "has taken a fork"))
			return (pthread_mutex_unlock(self->rfork), 1);
		pthread_mutex_lock(self->lfork);
	}
	philo_action(self, "has taken a fork");
	philo_action(self, "is eating");
	self->last_ate_stamp = get_timestamp(self->options->start_stamp);
	usleep(self->options->time_to_eat * 1000);
	pthread_mutex_unlock(self->lfork);
	pthread_mutex_unlock(self->rfork);
	return (0);
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
		philo_action(self, "is thinking");
		usleep(1000);
		if (philo_eat(self))
			return (NULL);
		++ate_count;
		if (ate_count == self->options->nb_iter)
		{
			pthread_mutex_lock(&self->options->counter.m);
			self->options->counter.count += 1;
			pthread_mutex_unlock(&self->options->counter.m);
		}
		philo_action(self, "is sleeping");
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
		if (philos->options->nb_iter)
		{
			pthread_mutex_lock(&philos->options->counter.m);
			if (philos->options->counter.count == philos->options->philo_count)
				break ;
			pthread_mutex_unlock(&philos->options->counter.m);
		}
		while (i < philos->options->philo_count)
		{
			if (get_timestamp(philos->options->start_stamp) - philos->options->time_to_die >=
				(philos[i].last_ate_stamp))
				{
					printf("%ld %d died\n", get_timestamp(philos->options->start_stamp), i + 1);
					pthread_mutex_lock(&philos->options->running_m);
					philos->options->running = 0;
					pthread_mutex_unlock(&philos->options->running_m);
					return ;
				}
			++i;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&philos->options->running_m);
	philos->options->running = 0;
	pthread_mutex_unlock(&philos->options->running_m);
}
