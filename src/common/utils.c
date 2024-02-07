/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arlarzil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:52:55 by arlarzil          #+#    #+#             */
/*   Updated: 2024/02/07 12:52:55 by arlarzil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(const char *s)
{
	const char	*e;

	e = s;
	while (*e)
		++e;
	return (e - s);
}

int	is_num(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(const char *s)
{
	int	res;
	int	sign;
	int	next;

	res = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*(s++) == '-')
			sign = -1;
	}
	else if (!is_num(*s))
		return (0);
	while (is_num(*s))
	{
		next = res * 10 + (*s - '0');
		if (next < res)
			return (0);
		res = next;
		++s;
	}
	if (sign == -1 && res * sign == res)
		return (0);
	return (res * sign);
}
