/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:57:39 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 19:48:11 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

// Returns 1 in case of success
int	action(t_philo *self, const char *text)
{
	suseconds_t stamp;

	if (qmutex_get(&self->opt->run_m, &self->opt->run))
	{
		pthread_mutex_lock(&self->opt->print_m);
		stamp = get_timestamp(self->opt->start);
		printf("%ld %d %s\n", stamp, self->num, text);
		pthread_mutex_unlock(&self->opt->print_m);
		return (1);
	}
	return (0);
}

static int	philo_step(t_philo *p, int *eat_count)
{
	if (!eat(p, eat_count))
		return (0);
	if (!action(p, "is sleeping"))
		return (0);
	usleep(p->opt->t_sleep * 1000);
	if (!action(p, "is thinking"))
		return (0);
	usleep(1000);
	return (1);
}

void	*routine(void *data)
{
	t_philo *self;
	int eat_count;

	eat_count = 0;
	self = data;
	if (self->num % 2 == 0)
		usleep(3000);
	action(self, "is thinking");
	while (philo_step(self, &eat_count))
		;
	return (NULL);
}
