#include <philo.h>
#include <stdio.h>

/*
** Fonction action: Si la simu run, dabloque le mutex de printf pour afficher
** le message adapté
*/

int	action(t_philo *self, const char *text)
{
	suseconds_t stamp;

	if (qmutex_get(&self->opt->run_m, &self->opt->run))
	{
		stamp = get_timestamp(self->opt->start);
		pthread_mutex_lock(&self->opt->print_m);
		printf("%ld %d %s\n", stamp, self->num, text);
		pthread_mutex_unlock(&self->opt->print_m);
		return (1);
	}
	return (0);
}
