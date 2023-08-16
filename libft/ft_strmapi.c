/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:12:12 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/02 13:07:34 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*sol;
	char			*cp_s;
	unsigned int	i;

	cp_s = (char *)s;
	i = 0;
	sol = ft_calloc(sizeof(*sol), ft_strlen(cp_s) + 1);
	if (sol == NULL)
		return (NULL);
	while (cp_s[i] != '\0')
	{
		sol[i] = (*f)(i, cp_s[i]);
		i++;
	}
	return (sol);
}
