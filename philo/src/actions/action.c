/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:38:52 by arlarzil          #+#    #+#             */
/*   Updated: 2024/08/25 12:38:52 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>

/*
** Fonction action: Si la simu run, dabloque le mutex de printf pour afficher
** le message adapté
*/

int	action(t_philo *self, const char *text)
{
	suseconds_t	stamp;
	int			ret;

	ret = 0;
	pthread_mutex_lock(&self->opt->run_m);
	if (self->opt->run)
	{
		stamp = get_timestamp(self->opt->start);
		pthread_mutex_lock(&self->opt->print_m);
		printf("%ld %d %s\n", stamp, self->num, text);
		pthread_mutex_unlock(&self->opt->print_m);
		ret = 1;
	}
	pthread_mutex_unlock(&self->opt->run_m);
	return (ret);
}
