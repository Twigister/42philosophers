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

# define MAX_THREADS	128

# include <pthread.h>
# include <sys/time.h>

typedef struct s_counter {
	pthread_mutex_t	m;
	int				count;
}	t_counter;

typedef struct s_options {
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_iter;
	suseconds_t		start_stamp;
	t_counter		counter;
	pthread_mutex_t	running_m;
	int				running;
}	t_options;

typedef struct s_philo {
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_options		*options;
	int				number;
	int				last_ate_stamp;
	pthread_t		thread;
}	t_philo;

int			ft_atoi(const char *s);
int			is_num(char c);
int			ft_strlen(const char *s);
void		print_err_exit(const char *msg);
t_philo		*init_philos(t_options *options);
void		destruct_philos(t_philo *philos, int philo_count);
void		ft_bzero(void *mem, unsigned int size);
void		*philo_routine(void	*data);
suseconds_t	get_timestamp(suseconds_t initial_timestamp);
void		philo_watcher(t_philo *philos);

#endif