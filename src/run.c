/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:09:22 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 19:15:32 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static int	check_death(t_philo *philo)
{
	suseconds_t	ts;
	int			ret;

	ret = 0;
	pthread_mutex_lock(&philo->m_last_ate);
	ts = get_timestamp(philo->opt->start);
	if (ts - philo->opt->t_die >= philo->last_ate)
	{
		action(philo, "died");
		ret = 1;
	}
	pthread_mutex_unlock(&philo->m_last_ate);
	return (ret);
}

static void	watch(t_philo *philo)
{
	t_options	*opt;
	int			i;

	opt = philo->opt;
	while (qmutex_get(&opt->run_m, &opt->run))
	{
		i = 0;
		usleep(1000);
		while (i < opt->p_count)
		{
			if (check_death(&philo[i]))
			{
				qmutex_set(&opt->run_m, &opt->run, 0);
				break ;
			}
			i += 1;
		}
	}
}

int	run_sim(t_philo *philo)
{
	int				i;
	t_options		*opt;
	struct timeval	tv;

	i = 0;
	opt = philo->opt;
	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "Error using gettimeofday\n", 26);
		return (1);
	}
	philo->opt->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (i < opt->p_count)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]))
		{
			destruct_partial(philo, i - 1, true);
			qmutex_set(&opt->run_m, &opt->run, -1);
			return (1);
		}
		i += 1;
	}
	watch(philo);
	return (0);
}
