/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:47:30 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/01 12:22:54 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	c1;
	char	*s1;

	c1 = (char)c;
	s1 = (char *)s;
	while (*s1 != '\0' && *s1 != c1)
		s1++;
	if (*s1 == c1)
		return (s1);
	else
		return (NULL);
}
/*
int main()
{
	char *s;
	s = "teste";
	
	int c = '\0' ;
	printf("%s\n",strchr(s,c));
	printf("%s\n",ft_strchr(s,c));
}*/
