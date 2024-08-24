/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:12 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/10 19:15:39 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_THREADS	128

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_options {
	int				p_count;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				it;
	pthread_mutex_t	print_m;
	pthread_mutex_t	run_m;
	pthread_mutex_t	count_m;
	suseconds_t		start;
	int				run;
	int				rem_count;
}	t_options;

typedef struct s_philo {
	pthread_mutex_t	*lfork;
	pthread_mutex_t	rfork;
	pthread_mutex_t	m_last_ate; // A init
	t_options		*opt;
	int				num;
	int				last_ate;
	pthread_t		thread;
}	t_philo;

int			ft_atoi(const char *s);
void		msleep(int msec);

t_philo		*init_philos(t_options *opt);
int			run_sim(t_philo *philo);
void		destruct(t_philo *philos);
void		destruct_common(t_options *opt);
void		destruct_partial(t_philo *tab, int i, bool thread);

void		*routine(t_philo *data);
int			action(t_philo *self, const char *text);
int			eat(t_philo *p, int *eat_count);

int			qmutex_get(pthread_mutex_t *m, int *val);
void		qmutex_set(pthread_mutex_t *m, int *val, int new);

void		waiter(t_philo*	philo);

suseconds_t	get_timestamp(suseconds_t initial_timestamp);

#endif
