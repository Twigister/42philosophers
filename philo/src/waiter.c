#include <philo.h>
#include <stdio.h>
#include <unistd.h>

static void	announce_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->opt->run_m);
	pthread_mutex_lock(&philo->opt->print_m);
	philo->opt->run = 0;
	printf("%ld %d died\n", get_timestamp(philo->opt->start), philo->num);
	pthread_mutex_unlock(&philo->opt->print_m);
	pthread_mutex_unlock(&philo->opt->run_m);

}

static int	check_death(t_philo *philo)
{
	suseconds_t	ts;
	int			ret;

	pthread_mutex_lock(&philo->m_last_ate);
	ts = get_timestamp(philo->opt->start);
	if (ts - philo->opt->t_die >= philo->last_ate)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&philo->m_last_ate);
	return (ret);
}

void	waiter(t_philo *philo)
{
	int			i;

	while (1)
	{
		i = 0;
		while (i < philo->opt->p_count)
		{
			if (check_death(philo + i))
			{
				announce_death(philo + i);
				return ;
			}
			if (qmutex_get(&philo->opt->count_m, &philo->opt->rem_count)
				== philo->opt->p_count)
			{
				qmutex_set(&philo->opt->run_m, &philo->opt->run, 0);
				return ;
			}
			i += 1;
		}
		msleep(10);
	}
}
