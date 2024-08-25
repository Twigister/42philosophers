/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:38:43 by arlarzil          #+#    #+#             */
/*   Updated: 2024/08/25 12:38:43 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

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
		if (pthread_create(&philo[i].thread, NULL,
				(void *(*)(void *))routine, &philo[i]))
		{
			destruct_partial(philo, i - 1, true);
			qmutex_set(&opt->run_m, &opt->run, -1);
			return (1);
		}
		i += 1;
	}
	waiter(philo);
	return (0);
}
