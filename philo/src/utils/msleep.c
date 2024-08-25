/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 12:39:02 by arlarzil          #+#    #+#             */
/*   Updated: 2024/08/25 12:39:02 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

static long	mstime(void)
{
	struct timeval	ini;

	gettimeofday(&ini, 0);
	return (ini.tv_sec * 1000 + ini.tv_usec / 1000);
}

void	msleep(int msec)
{
	long	goal;

	goal = mstime() + msec;
	while (goal > mstime())
	{
		usleep(50);
	}
}
