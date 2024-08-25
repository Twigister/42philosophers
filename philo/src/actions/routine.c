/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:39:08 by arlarzil          #+#    #+#             */
/*   Updated: 2024/08/25 12:39:08 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*routine(t_philo *self)
{
	int	eat_count;

	eat_count = 0;
	if (!action(self, "is thinking"))
		return (NULL);
	while (1)
	{
		if (self->num % 2)
			msleep(6);
		if (!eat(self, &eat_count))
			break ;
		if (!action(self, "is sleeping"))
			break ;
		msleep(self->opt->t_sleep);
		if (!action(self, "is thinking"))
			break ;
		msleep(self->opt->t_eat - self->opt->t_sleep);
	}
	return (NULL);
}
