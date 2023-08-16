/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:51:15 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/01 17:29:13 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	char	*sol;

	if (s1 == NULL)
		return (NULL);
	else if (!set)
		return (ft_strdup(s1));
	if (ft_strncmp(s1, set, ft_strlen(s1)) == 0)
		return (ft_strdup(""));
	first = 0;
	last = ft_strlen(s1) - 1;
	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	first = i;
	i = ft_strlen(s1) - 1;
	while (i > first && ft_strchr(set, s1[i]) != NULL)
			i--;
	last = i;
	sol = ft_substr(s1, first, last - first + 1);
	return (sol);
}
/*
int main ()
{

	printf("%s\n",ft_strtrim("",""));
	printf("%d\n",ft_strncmp("","",0));
}*/
