/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:45:59 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 13:16:00 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}
/*
int main()
{
	char	test[20];
	char	dest [15];

	test[0] = 'a';
	test[1] = 'b';
	test[2] = 'c';
	test[3] = 'd';
	dest[0] = 'z';
	printf("%s\n",dest);
	printf("%s\n",memcpy(test,dest,(5)));
}*/
