/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:00:03 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/07 13:00:05 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct	s_options {
	int	philo_count;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_iter;
}	t_options;

typedef struct s_philo {
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_options		*options;
}	t_philo;

int		ft_atoi(const char *s);
int		is_num(char c);
int		ft_strlen(const char *s);
void	print_err_exit(const char *msg);
t_philo *init_philos(t_options *options);
void	destruct_philos(t_philo *philos, int philo_count);
void	ft_bzero(void *mem, unsigned int size);

#endif