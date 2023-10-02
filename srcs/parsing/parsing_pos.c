/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/02 11:10:31 by lsohler          ###   ########.fr       */
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

float	ft_get_float(char *line)
{
	float	pos;
	int		j;
	float	decimal;

	pos = ft_atoi(line);
	j = 0;
	if (line[j] == '-')
		j++;
	j = ft_isalldigit(line, '.', j);
	j++;
	ft_isalldigit(line, '\0', j);
	decimal = ft_getdec(line, '\0', j);
	if (line[0] == '-')
		pos = pos - ft_atoi(line + j) / decimal;
	else
		pos = pos + ft_atoi(line + j) / decimal;
	return (pos);
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
	pos.x = ft_get_float(split[0]);
	pos.y = ft_get_float(split[1]);
	pos.z = ft_get_float(split[2]);
	return (pos);
}
