/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:26:52 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 15:15:08 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(b + i) = '\0';
		i++;
	}
}
/*
int  main()
{
	char test[20];

	test[0] = 'a';
	test[1] = 'a';
	test[2]= 'b';
	test[3] = 'c';
	printf("%s\n",test);
	printf("%s\n",bzero(test,(0)));
	printf("%s\n",ft_bzero(test,(0)));
	return (0);
}*/				
