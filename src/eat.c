/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:28:39 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 21:28:30 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	rl_eat(t_philo *p)
{
	int	ret;

	pthread_mutex_lock(&p->rfork);
	if (action(p, "has taken a fork"))
		return (pthread_mutex_unlock(&p->rfork), 1);
	pthread_mutex_lock(p->lfork);
	if (action(p, "has taken a fork"))
	{
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(&p->rfork);
		return (1);
	}
	ret = action(p, "is eating");
	pthread_mutex_lock(&p->m_last_ate);
	p->last_ate = get_timestamp(p->opt->start);
	pthread_mutex_unlock(&p->m_last_ate);
	if (!ret)
		usleep(p->opt->t_eat * 1000);
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(&p->rfork);
	return (ret);
}

static int	lr_eat(t_philo *p)
{
	int	ret;

	pthread_mutex_lock(p->lfork);
	if (action(p, "has taken a fork"))
		return (pthread_mutex_unlock(p->lfork), 1);
	pthread_mutex_lock(&p->rfork);
	if (action(p, "has taken a fork"))
	{
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(&p->rfork);
		return (1);
	}
	ret = action(p, "is eating");
	pthread_mutex_lock(&p->m_last_ate);
	p->last_ate = get_timestamp(p->opt->start);
	pthread_mutex_unlock(&p->m_last_ate);
	if (!ret)
		usleep(p->opt->t_eat * 1000);
	pthread_mutex_unlock(p->lfork);
	pthread_mutex_unlock(&p->rfork);
	return (ret);
}

void	test_eat_count(int n, t_philo *p)
{
	int	temp;

	if (p->opt->it != -1 && n == p->opt->it)
	{
		temp = qmutex_get(&p->opt->count_m, &p->opt->rem_count);
		qmutex_set(&p->opt->count_m, &p->opt->rem_count, temp + 1);
		if (p->opt->p_count == qmutex_get(&p->opt->count_m,
			&p->opt->rem_count))
			qmutex_set(&p->opt->run_m, &p->opt->run, 0);
	}
}

int	eat(t_philo *p, int *eat_count)
{
	if (p->num % 2)
	{
		usleep(100);
		if (rl_eat(p))
			return (1);
	}
	else
	{
		if (lr_eat(p))
			return (1);
	}
	*eat_count += 1;
	test_eat_count(*eat_count, p);
	return (0);
}
