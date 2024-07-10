/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <arlarzil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:28:57 by arlarzil          #+#    #+#             */
/*   Updated: 2024/07/09 16:07:20 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	sign = 1;
	i = 0;
	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		++str;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}
