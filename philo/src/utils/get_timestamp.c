/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_timestamp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:32:46 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 19:53:42 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

suseconds_t	get_timestamp(suseconds_t initial_timestamp)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000 - initial_timestamp);
}
