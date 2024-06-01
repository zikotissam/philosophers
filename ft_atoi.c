/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlakhdar <zlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:24:56 by zlakhdar          #+#    #+#             */
/*   Updated: 2024/05/14 22:09:17 by zlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	calcule_result(const char *str, int sign)
{
	long		result;
	long		i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		if (result > INT_MAX)
		{
			if ((sign == -1 && result * -1 < INT_MIN) || (sign == 1 && result > INT_MAX))
			{
				write(2, "ERROR\n", 6);
				return (-1);
			}
		}
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *nptr)
{
	long			sign;
	long			i;

	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	return (calcule_result(&nptr[i], sign));
}
