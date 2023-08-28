/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_diam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:55:26 by itovar-n          #+#    #+#             */
/*   Updated: 2023/08/28 21:48:07 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_get_float_d(char *line)
{
	float	pos;
	int		j;
	int		len;

	pos = ft_atoi(line);
	j = 0;
	if (line[j] != '-')
		j++;
	while (line[j] != '.')
	{
		if (ft_isdigit(line[j]) == 0)
			ft_exit();
		j++;
	}
	j++;
	len = ft_strlen(line + j);
	if (line[0] == '-' && ft_isdigit(line[j]) == 1
		&& ft_isdigit(line[j + 1]) == 1)
		pos = pos - ft_atoi(line + j) / len;
	else if (ft_isdigit(line[j]) == 1 && ft_isdigit(line[j + 1]) == 1)
		pos = pos + ft_atoi(line + j) / len;
	if (ft_isdigit(line[j]) == 0 || line[j + 2] != '\0')
		ft_exit();
	return (pos);
}
