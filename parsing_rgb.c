/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:19:22 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_rgb(char *line)
{
	int	pos;
	int	j;

	pos = ft_atoi(line);
	j = 0;
	if (pos < 0 || pos > 255)
		ft_exit();
	while (line[j] != '\0')
	{
		if (ft_isdigit(line[j]) == 0)
			ft_exit();
		j++;
	}
	return (pos);
}

int	*ft_rgb(char *line)
{
	char	**split;
	int		i;
	int		*pos;

	i = 0;
	split = ft_split(line, ',');
	pos = malloc(sizeof(int) * 3);
	if (!pos)
		return (NULL);
	while (i < 3)
	{
		if (!split[i])
			ft_exit();
		pos[i] = ft_get_rgb(split[i]);
		i++;
	}
	if (split[3])
		ft_exit();
	ft_free_cc(split);
	return (pos);
}

