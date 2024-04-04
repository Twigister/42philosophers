/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:05:33 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/22 17:06:49 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	destruct_philos(t_philo *philos, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_cancel(philos[i].thread) == 0)
		{
			// pthread_mutex_unlock(philos[i].lfork); // C pos bon
			pthread_join(philos[i].thread, NULL);
			pthread_mutex_destroy(philos[i].lfork);
			free(philos[i].lfork);
		}
		++i;
	}
	free(philos);
}
