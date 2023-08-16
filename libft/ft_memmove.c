/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:17:41 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 15:23:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t len)
{
	unsigned char	*dest1;
	unsigned char	*src1;
	size_t			i;

	if (dest == 0 && src == 0)
		return (NULL);
	if (len == 0)
		return (dest);
	dest1 = (unsigned char *)dest;
	src1 = (unsigned char *)src;
	i = 0;
	if (src1 < dest1)
	{
		while (len--)
			dest1[len] = src1[len];
	}
	else
	{
		while (i < len)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dest);
}
