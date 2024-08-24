/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:25:59 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 18:17:33 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

int	usage(void)
{
	write(2, "Usage: ./philo number_of_philosophers ", 38);
	write(2, "time_to_die time_to_eat time_to_sleep ", 38);
	write(2, "[number_of_times_each_philosopher_must_eat]\n", 45);
	return (1);
}

static int	handle_args(t_options *opt, int ac, char **av)
{
	if (5 > ac || ac > 6)
		return (1);
	opt->p_count = ft_atoi(av[1]);
	opt->t_die = ft_atoi(av[2]);
	opt->t_eat = ft_atoi(av[3]);
	opt->t_sleep = ft_atoi(av[4]);
	if (opt->p_count <= 0 || opt->t_die <= 0
		|| opt->t_eat <= 0 || opt->t_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		opt->it = ft_atoi(av[5]);
		if (opt->it <= 0)
			return (1);
	}
	else
		opt->it = -1;
	return (0);
}

int	main(int ac, char **av)
{
	t_options	philos;
	t_philo		*philo_data;

	if (handle_args(&philos, ac, av))
		return (usage());
	philo_data = init_philos(&philos);
	if (!philo_data || run_sim(philo_data))
		return (write(2, "Memory error\n", 14), 1);
	destruct(philo_data);
}
