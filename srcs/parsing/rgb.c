/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/15 15:08:52 by lsohler          ###   ########.fr       */
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
		ft_exit("RGB overflow");
	while (line[j] != '\0')
	{
		if (ft_isdigit(line[j]) == 0)
			ft_exit("RGB is not a digit");
		j++;
	}
	return (pos);
}

t_rgb	ft_rgb(char *line)
{
	char	**split;
	int		i;
	t_rgb	rgb;

	i = 0;
	split = ft_split(line, ',');
	while (split[i])
		i++;
	if (i != 3)
		ft_exit("POS syntax");
	rgb.r = ft_get_rgb(split[0]);
	rgb.g = ft_get_rgb(split[1]);
	rgb.b = ft_get_rgb(split[2]);
	free_array(split);
	return (rgb);
}
