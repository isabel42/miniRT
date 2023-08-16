/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:29:26 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/02 14:38:53 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sizea(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		size++;
		n = n * (-1);
	}
	while (n >= 1)
	{
		size++;
		n = (n - n % 10) / 10;
	}
	return (size);
}

char	*ft_allocsol(char *sol, int size, int sign, int n)
{
	while (size > 0 && size > -1 * sign)
	{
		sol[size - 1] = (n % 10) * sign + 48;
		n = (n - n % 10) / 10;
		size--;
	}
	return (sol);
}

char	*ft_itoa(int n)
{
	char	*sol;
	int		size;
	int		sign;

	sign = 1;
	size = ft_sizea(n);
	sol = malloc(sizeof(*sol) * (size + 1));
	if (sol == NULL)
		return (NULL);
	sol[size] = '\0';
	if (n < 0)
	{
		sign = -1;
		sol [0] = '-';
	}
	sol = ft_allocsol(sol, size, sign, n);
	return (sol);
}
/*
int main ()
{
	int b = -2147483648;
	printf("%s\n",ft_itoa(b));
}*/
