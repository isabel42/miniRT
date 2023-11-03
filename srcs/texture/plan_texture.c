/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:01:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 15:18:18 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	get_texture_from_plane(t_vec3d pos, t_vec3d normal, t_data_img *texture)
{
	int	x;
	int	y;

	(void)normal;
	if (fabs(ft_dot(normal, (t_vec3d){1, 0, 0})) == 1)
		x = (int)pos.z % texture->width;
	else
		x = (int)pos.x % texture->width;
	if (x < 0)
		x = texture->width - x;
	if (fabs(ft_dot(normal, (t_vec3d){0, 1, 0})) == 1)
		y = (texture->height - 1) - abs((int)pos.z
				% texture->height);
	else
		y = (texture->height - 1) - abs((int)pos.y
				% texture->height - 1);
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
