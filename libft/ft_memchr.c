/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:23:07 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 15:23:56 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*s1 == (unsigned char)c)
			return (s1);
		i++;
		s1++;
	}
	return (NULL);
}
/*
int main()
{
	printf("%s\n",ft_memchr("bonjour", 'o',7));
}*/
