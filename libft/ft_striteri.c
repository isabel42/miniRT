/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:07:49 by itovar-n          #+#    #+#             */
/*   Updated: 2022/11/02 13:42:01 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	char			*ad_s;

	i = 0;
	ad_s = s;
	while (s[i] != '\0')
	{
		(*f)(i, ad_s);
		i++;
		ad_s++;
	}
}
