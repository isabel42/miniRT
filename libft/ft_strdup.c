/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:16:38 by itovar-n          #+#    #+#             */
/*   Updated: 2022/10/31 15:46:33 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void		*cp_s1;
	size_t		len;

	len = ft_strlen(s1);
	cp_s1 = ft_calloc(len + 1, sizeof(*s1));
	if (cp_s1 == NULL)
		return (NULL);
	ft_memcpy(cp_s1, s1, len);
	return (cp_s1);
}
