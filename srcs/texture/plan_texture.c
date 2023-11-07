/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/07 11:45:17 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_texture_from_plane(t_vec3d pos, t_vec3d normal, t_data_img *texture)
{
	int	x;
	int	y;

	if (fabs(ft_dot(normal, (t_vec3d){1, 0, 0})) == 1)
		x = (int)pos.z;
	else
		x = (int)pos.x;
	if (fabs(ft_dot(normal, (t_vec3d){0, 1, 0})) == 1)
		y = (int)pos.z;
	else
		y = (int)pos.y;
	if (!ft_range(0, x, texture->width) || !ft_range(-(texture->width), x, 0))
		x %= texture->width;
	if (!ft_range(0, y, texture->width) || !ft_range(-texture->width, y, 0))
		y %= texture->height;
	if (x < 0)
		x = texture->width - -x;
	if (y < 0)
		y = texture->width - -y;
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
