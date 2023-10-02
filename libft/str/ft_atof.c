/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:03:08 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/02 18:00:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_get_dec(const char *str)
{
	double		nb;
	double		dec;
	int			i;
	int			j;

	nb = 0.0;
	dec = 0.0;
	i = 0;
	j = 0;
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10.0) + (*(str++) - '0');
	if (*(str++) == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			dec = (dec * 10.0) + (*(str++) - '0');
			i++;
		}
	}
	while (j++ < i)
		dec /= 10.0;
	if (*str == ',')
		return (nb + dec);
	return (nb + dec);
}

double	ft_atof(const char *str)
{
	int			sign;
	double		res;

	res = 0.0;
	sign = 1;
	if (!*str)
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = ft_get_dec(str);
	return (res * sign);
}
