/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 21:46:17 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_texture_from_plane(t_vec3d pos, t_vec3d normal, t_data_img *texture)
{
	int	x;
	int	y;

	if (fabs(ft_dot(normal, (t_vec3d){1, 0, 0})) == 1)
	{
		x = abs((int)pos.z) % texture->width;
		if (pos.z < 0.0)
			x = texture->width - x;
	}
	else
	{
		x = abs((int)pos.x) % texture->width;
		if (pos.x < 0.0)
			x = texture->width - x;
	}
	if (fabs(ft_dot(normal, (t_vec3d){0, 1, 0})) == 1)
	{
		y = abs((int)pos.z) % texture->width;
		if (pos.z < 0.0)
			y = texture->width - y;
	}
	else
	{
		y = abs((int)pos.x) % texture->width;
		if (pos.x < 0.0)
			y = texture->width - y;
	}
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
