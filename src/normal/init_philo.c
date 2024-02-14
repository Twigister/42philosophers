#include "philo.h"
#include <stdlib.h>

static void	new_philo(pthread_mutex_t *l, pthread_mutex_t *r, 
	t_philo *dest, t_options *options)
{
	dest->lfork = l;
	dest->rfork = r;
	dest->options = options;
}

static void	swap_mutex_ptr(pthread_mutex_t **a, pthread_mutex_t **b)
{
	pthread_mutex_t	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// On crée notre propre fonction pour pouvoir free en cas d'erreur
static void	mutex_creator(t_philo *list, int index, pthread_mutex_t **dest)
{
	int	i;
	pthread_mutex_t	*tmp;

	tmp = malloc(sizeof(pthread_mutex_t));
	if (tmp && pthread_mutex_init(tmp, NULL) == 0)
		*dest = tmp;
	else
	{
		i = 0;
		free(tmp);
		free(*dest);
		while (i < index)
		{
			if (list[i].lfork)
			{
				pthread_mutex_destroy(list[i].lfork);
				free(list[i].lfork);
			}
			++i;
		}
		free(list[i].rfork);
		free(list);
		print_err_exit("mutex initialisation failed");
	}
}

// Gestion d'erreur création de mutex a réaliser
static void	fill_philo_tab(t_options *options, t_philo *philos)
{
	int	i;
	pthread_mutex_t	*fst;
	pthread_mutex_t	*l;
	pthread_mutex_t	*r;

	i = 1;
	fst = NULL;
	r = NULL;
	l = NULL;
	mutex_creator(philos, 0, &fst);
	if (options->philo_count != 1)
		mutex_creator(philos, 0, &r);
	else
		r = fst;
	new_philo(fst, r, philos, options);
	while (i < options->philo_count - 1)
	{
		swap_mutex_ptr(&r, &l);
		mutex_creator(philos, i, &r);
		new_philo(l, r, philos + i, options);
		++i;
	}
	if (options->philo_count > 1)
		new_philo(r, fst, philos + i, options);
}

t_philo *init_philos(t_options *options)
{
	t_philo	*res;

	res = malloc(sizeof(t_philo) * options->philo_count);
	if (!res)
		print_err_exit("malloc failed");
	ft_bzero(res, sizeof(t_philo) * options->philo_count);
	fill_philo_tab(options, res);
	return (res);
}
