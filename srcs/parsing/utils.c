/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/15 15:13:24 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_getdec(char *line, char end, int start)
{
	int	j;
	int	res;

	j = 0;
	res = 1;
	while (line[start + j] != end)
	{
		res = res * 10;
		j++;
	}
	return (res);
}

int	ft_isalldigit(char *line, char end, int start)
{
	int	j;

	j = 0;
	while (line[start + j] != end && line[start + j] != '\0')
	{
		if (ft_isdigit(line[start + j]) == 0)
			ft_exit("Not a digit");
		j++;
	}
	return (j);
}

t_vec3d	ft_pos(char *line)
{
	char	**split;
	int		i;
	t_vec3d	pos;

	i = 0;
	split = ft_split(line, ',');
	while (split[i])
		i++;
	if (i != 3)
		ft_exit("POS syntax");
	pos.x = ft_atof(split[0]);
	pos.y = ft_atof(split[1]);
	pos.z = ft_atof(split[2]);
	free_array(split);
	return (pos);
}
