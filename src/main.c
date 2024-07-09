/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:25:59 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 17:16:03 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	usage(void)
{
	write(2, "Usage: ./philo number_of_philosophers ", 38);
	write(2, "time_to_die time_to_eat time_to_sleep ", 38);
	write(2, "[number_of_times_each_philosopher_must_eat]\n", 45);
	return (1);
}

int	main(int ac, char **av)
{
	t_options	philos;
	t_philo		*philo_data;

	if (5 > ac || ac > 6)
		return (usage());
	philos.p_count = ft_atoi(av[1]);
	philos.t_die = ft_atoi(av[2]);
	philos.t_eat = ft_atoi(av[3]);
	philos.t_sleep = ft_atoi(av[4]);
	if (philos.p_count <= 0 || philos.t_die <= 0
		|| philos.t_eat <= 0 || philos.t_sleep <= 0)
		return (usage());
	if (ac == 6)
	{
		philos.it = ft_atoi(av[5]);
		if (philos.it <= 0)
			return (usage());
	}
	else
		philos.it = -1;
	philo_data = init_philos(&philos);
	if (!philo_data || run_sim(philo_data))
		return (write(2, "Memory error\n", 14), 1);
	destruct(philo_data);
}
