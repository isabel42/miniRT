/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:47:30 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 14:00:14 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	c1;
	char	*s1;
	char	*saved_c;

	c1 = (char)c;
	s1 = (char *)s;
	saved_c = NULL;
	while (*s1 != '\0')
	{
		if (*s1 == c1)
			saved_c = s1;
		s1++;
	}
	if (*s1 == c1)
		return (s1);
	else
		return (saved_c);
}
/*
int main()
{
	char *s;
	s = "teste";
	
	int c ='\0';
	printf("%s\n",strrchr(s,c));
	printf("%s\n",ft_strrchr(s,c));
}*/
