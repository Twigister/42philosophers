/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:57:39 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 21:13:08 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>

/*
		if (opt->it != -1)
		{
			if (qmutex_get(&opt->count_m, &opt->rem_count) == opt->p_count)
			{ // Check a faire faire par le philo
				qmutex_set(&opt->run_m, &opt->run, 0);
			}
*/
int	action(t_philo *self, const char *text)
{
	suseconds_t	stamp;

	if (qmutex_get(&self->opt->run_m, &self->opt->run) == 0)
		return (1);
	stamp = get_timestamp(self->opt->start);
	pthread_mutex_lock(&self->opt->print_m);
	printf("%ld %d %s\n", stamp, self->num, text);
	pthread_mutex_unlock(&self->opt->print_m);
	return (0);
}

static int	wait_start(pthread_mutex_t *m, int *val)
{
	int	ret;

	ret = 0;
	while (!ret)
	{
		ret = qmutex_get(m, val);
		usleep(10);
	}
	return (ret);
}

static int	philo_step(t_philo *p, int *eat_count)
{
	usleep(1000);
	if (action(p, "is thinking"))
		return (0);
	if (eat(p, eat_count))
		return (0);
	if (action(p, "is sleeping"))
		return (0);
	return (1);
}

void	*routine(void *data)
{
	t_philo	*self;
	int		flag = 1;
	int		eat_count;

	eat_count = 0;
	self = data;
	flag = wait_start(&self->opt->run_m, &self->opt->run);
	if (self->num % 2)
		usleep(8800);
	if (flag == -1)
		return (NULL);
	while (philo_step(self, &eat_count))
		;
	return (NULL);
}
