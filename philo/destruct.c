/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:38 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 20:58:24 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	destruct_common(t_options *opt)
{
	pthread_mutex_destroy(&opt->print_m);
	pthread_mutex_destroy(&opt->run_m);
	pthread_mutex_destroy(&opt->count_m);
}

void	destruct_partial(t_philo *philo, int n, bool thread)
{
	int		i;
	void	*ret;

	i = 0;
	while (i < n)
	{
		if (thread)
			pthread_join(philo[i].thread, &ret);
		pthread_mutex_destroy(&philo[i].rfork);
		i += 1;
	}
	if (thread)
	{
		while (i < philo->opt->p_count)
		{
			pthread_mutex_destroy(&philo[i].rfork);
			i += 1;
		}
	}
	destruct_common(philo->opt);
}

void	destruct(t_philo *philos)
{
	int			i;
	t_options	*opt;
	void		*ret;

	i = 0;
	opt = philos->opt;
	while (i < opt->p_count)
	{
		pthread_join(philos[i].thread, &ret);
		i += 1;
	}
	i = 0;
	while (i < opt->p_count)
	{
		pthread_mutex_destroy(&philos[i].rfork);
		i += 1;
	}
	destruct_common(opt);
	free(philos);
}
