#include <stdlib.h>
#include "philo.h"

void	destruct_philos(t_philo *philos, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_destroy(philos[i].lfork);
		free(philos[i].lfork);
		++i;
	}
	free(philos);
}
