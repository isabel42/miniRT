/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/11/03 17:09:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

float	get_ratio(char *line, float min, float max)
{
	float	res;

	res = ft_atof(line);
	if (res < min || res > max)
		ft_exit("Incorrect value range");
	return (res);
}

t_vec3d	get_orientation(char *line, float min, float max)
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
	pos.x = get_ratio(split[0], min, max);
	pos.y = get_ratio(split[1], min, max);
	pos.z = get_ratio(split[2], min, max);
	if (pos.x == 0 && pos.y == 0 && pos.z == 0)
		ft_exit("0 0 0 is not a valid orientation");
	free_array(split);
	return (pos);
}
