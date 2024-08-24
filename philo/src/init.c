/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:01 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 19:14:50 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static int	init_common(t_options *opt)
{
	if (pthread_mutex_init(&opt->print_m, NULL))
		return (1);
	if (pthread_mutex_init(&opt->run_m, NULL))
		return (pthread_mutex_destroy(&opt->print_m), 1);
	if (pthread_mutex_init(&opt->count_m, NULL))
	{
		pthread_mutex_destroy(&opt->print_m);
		pthread_mutex_destroy(&opt->run_m);
		return (1);
	}
	opt->run = 1;
	opt->rem_count = 0;
	return (0);
}

static int	fill_tab(t_philo *tab, t_options *opt)
{
	int				i;
	pthread_mutex_t	*prev;

	i = 0;
	prev = NULL;
	while (i < opt->p_count)
	{
		tab[i].opt = opt;
		tab[i].lfork = prev;
		tab[i].num = i + 1;
		tab[i].last_ate = 0;
		if (pthread_mutex_init(&tab[i].rfork, NULL))
		{
			destruct_partial(tab, i - 1, false);
			free(tab);
			return (1);
		}
		if (pthread_mutex_init(&tab[i].m_last_ate, NULL))
		{
			pthread_mutex_destroy(&tab[i].m_last_ate);
			destruct_partial(tab, i - 1, false);
			free(tab);
			return (1);
		}
		prev = &tab[i].rfork;
		i += 1;
	}
	tab[0].lfork = prev;
	return (0);
}

t_philo	*init_philos(t_options *opt)
{
	t_philo	*philos;

	if (init_common(opt))
		return (NULL);
	philos = malloc(sizeof(t_philo) * opt->p_count);
	if (!philos)
		return (NULL);
	if (fill_tab(philos, opt))
		return (NULL);
	return (philos);
}
