/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:28:37 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:49:02 by itovar-n         ###   ########.fr       */
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
			ft_exit();
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

float	*ft_pos(char *line)
{
	char	**split;
	int		i;
	float	*pos;

	i = 0;
	split = ft_split(line, ',');
	pos = malloc(sizeof(float) * 3);
	if (!pos)
		return (NULL);
	while (i < 3)
	{
		if (!split[i])
			ft_exit();
		pos[i] = ft_get_float(split[i]);
		i++;
	}
	if (split[3])
		ft_exit();
	ft_free_cc(split);
	return (pos);
}
