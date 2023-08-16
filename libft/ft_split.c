/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:32:34 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/08 11:55:22 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countsplit(char *s, char c)
{
	int	i;
	int	count;
	int	lasttime;

	i = 0;
	count = 0;
	lasttime = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && lasttime == 0)
		{
			count++;
			lasttime++;
		}
		else if (s[i] == c)
			lasttime = 0;
		i++;
	}
	return (count);
}

int	ft_countuc(char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

char	**ft_allocatesol(char **sol, char *s, char c)
{
	int	i;
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (j < ft_countsplit(s, c))
	{
		i = 0;
		while (s[k] == c)
			k++;
		sol [j] = ft_calloc(sizeof(char), ft_countuc(s, c, k) + 1);
		if (sol == NULL)
			return (NULL);
		while (s[k] != c && s[k] != '\0')
		{
			sol[j][i] = s[k];
			i++;
			k++;
		}
		j++;
	}
	return (sol);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	char	*cp_s;

	cp_s = (char *)s;
	sol = ft_calloc(sizeof (*sol), (ft_countsplit(cp_s, c) + 1));
	if (sol == NULL)
		return (NULL);
	sol = ft_allocatesol(sol, cp_s, c);
	return (sol);
}
/*
int main()
{
	char *s = "hello!";
	char **split;
	char c = ' ';
	int i = 0;
	split = ft_split(s,c);
	printf("%d\n",ft_countuc(s,c,i));
	printf("%d\n",ft_countsplit(s,c));
	printf("%s\n",split[0]);
	printf("%s\n",split[1]);
	printf("%zu\n",ft_strlen("e"));
}*/
