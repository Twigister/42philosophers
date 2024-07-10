/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:28:39 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 19:32:05 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	test_eat_count(int n, t_philo *p)
{
	int	temp;

	if (p->opt->it != -1 && n == p->opt->it)
	{
		temp = qmutex_get(&p->opt->count_m, &p->opt->rem_count);
		qmutex_set(&p->opt->count_m, &p->opt->rem_count, temp + 1);
		if (p->opt->p_count == qmutex_get(&p->opt->count_m,
			&p->opt->rem_count))
		{
			qmutex_set(&p->opt->run_m, &p->opt->run, 0);
			return (0);
		}
	}
	return (1);
}

static int	wait_death(t_philo *p)
{
	usleep(p->opt->t_die * 1000);
	pthread_mutex_unlock(&p->rfork);
	return (0);
}

int	eat(t_philo *p, int *eat_count)
{
	int	ret;

	pthread_mutex_lock(&p->rfork);
	if (!action(p, "has taken a fork"))
		return (pthread_mutex_unlock(&p->rfork), 0);
	if (p->opt->p_count == 1)
		return (wait_death(p));
	pthread_mutex_lock(p->lfork);
	ret = action(p, "has taken a fork") && action(p, "is eating");
	if (ret)
	{
		qmutex_set(&p->m_last_ate, &p->last_ate, get_timestamp(p->opt->start));
		*eat_count += 1;
		test_eat_count(*eat_count, p);
		usleep(p->opt->t_eat * 1000);
	}
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(&p->rfork);
	return (ret);
}
