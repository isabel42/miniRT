/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:36:30 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 12:12:46 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	size_t			i;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (i < n && s11[i] == s22[i]
		&& s11[i] != '\0' && s22[i] != '\0')
		i++;
	if (n == i)
		return (0);
	else
		return (s11[i] - s22[i]);
}
/*
int main()
{
	char *s1 = "test\0";
	char *s2 = "test\200";
	printf("%d\n",strncmp(s1,s2,6));
	printf("%d\n",ft_strncmp(s1,s2,6));
}*/
