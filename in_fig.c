/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_fig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:04:31 by itovar-n          #+#    #+#             */
/*   Updated: 2023/09/07 11:29:27 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_is_pl(t_obj *obj, float x, float y, float z)
{
	float *vector;
	float sin;

	vector = ft_vector(obj->pos[0] - x, obj->pos[1] - y, obj->pos[0] - z);
	if (!ft_sin (vector, obj->dir))
	{
		free(vector);
		return (1);
	}
	free(vector);
	return (0);
}

int ft_is_sp(t_obj *obj, float x, float y, float z)
{
	float *vector;

	vector = ft_vector(obj->pos[0] - x, obj->pos[1] - y, obj->pos[0] - z);
	if (ft_mod(vector) < obj->diam)
	{
		free(vector);
		return (1);
	}
	free(vector);
	return (0);
}
