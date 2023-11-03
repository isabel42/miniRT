/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:26:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:42:43 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cartesian_to_spherical(t_vec3d pos, float r, float *theta, float *phi)
{
	*phi = acos(pos.z / r);
	*theta = atan2(pos.y, pos.x);
}

t_rgb	get_texture_from_sphere(t_vec3d pos, float r, t_data_img *texture)
{
	float	theta;
	float	phi;
	int		x;
	int		y;

	cartesian_to_spherical(pos, r, &theta, &phi);
	x = ((int)((theta / (2 * M_PI)) * texture->width) % texture->width);
	y = ((int)((phi / M_PI) * texture->height) % texture->height);
	// x = (int)(fmodf((theta + M_PI) / (2 * M_PI), 1) * texture->width);
	// y = (int)(fmodf((phi + M_PI_2) / M_PI, 1) * texture->height);
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}
