/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:20:58 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 19:50:16 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

int	qmutex_get(pthread_mutex_t *m, int *val)
{
	int	ret;

	pthread_mutex_lock(m);
	ret = *val;
	pthread_mutex_unlock(m);
	return (ret);
}

void	qmutex_set(pthread_mutex_t *m, int *val, int new)
{
	pthread_mutex_lock(m);
	*val = new;
	pthread_mutex_unlock(m);
}
