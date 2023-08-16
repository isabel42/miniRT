/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:54:27 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/01 10:49:52 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sol;
	size_t	i;
	size_t	len_s;

	i = 0;
	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		len = 0;
	else if (ft_strlen(s + start) <= len)
		len = len_s - start;
	sol = ft_calloc(sizeof(*s), len + 1);
	if (sol == NULL)
		return (NULL);
	while (i < len)
	{
		sol[i] = s[start + i];
		i++;
	}
	return (sol);
}
/*
int main()
{
	ft_substr("hola", 10, 99);
}*/
