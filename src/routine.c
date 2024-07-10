/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:57:39 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 15:28:15 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

int	action(t_philo *self, const char *text)
{
	suseconds_t	stamp;

	usleep(1000);
	if (qmutex_get(&self->opt->run_m, &self->opt->run) == 0)
		return (1);
	stamp = get_timestamp(self->opt->start);
	pthread_mutex_lock(&self->opt->print_m);
	printf("%ld %d %s\n", stamp, self->num, text);
	pthread_mutex_unlock(&self->opt->print_m);
	return (0);
}

static int	philo_step(t_philo *p, int *eat_count)
{
	if (action(p, "is thinking"))
		return (0);
	usleep(2000);
	if (eat(p, eat_count))
		return (0);
	if (action(p, "is sleeping"))
		return (0);
	return (1);
}

void	*routine(void *data)
{
	t_philo	*self;
	int		eat_count;

	eat_count = 0;
	self = data;
	if (self->num % 2 == 0)
		usleep(1000);
	while (philo_step(self, &eat_count))
		;
	return (NULL);
}
