/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:36:30 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 15:24:32 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (i < n && s11[i] == s22[i])
		i++;
	if (n == i)
		return (0);
	return (s11[i] - s22[i]);
}
/*
int main()
{
	char *s1 = "aaaa";
	char *s2 = "aab";
	printf("%d\n",memcmp(s1,s2,4));
	printf("%d\n",ft_memcmp(s1,s2,4));
}*/
