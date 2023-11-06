/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:26:49 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/05 17:59:42 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cartesian_to_spherical(t_vec3d pos, float r, float *theta, float *phi)
{
	*theta = atan2(pos.y, pos.x);
	if (*theta < 0)
		*theta += 2 * M_PI;
	*phi = acos(pos.z / r);
}

t_rgb	get_texture_from_sphere(t_vec3d pos, float r, t_data_img *texture)
{
	float	theta;
	float	phi;
	int		x;
	int		y;

	cartesian_to_spherical(pos, r, &theta, &phi);
	x = (int)(theta / (2 * M_PI) * texture->width);
	y = (int)(phi / M_PI * texture->height);
	x = texture->width - x;
	return (int_to_rgb(get_color_from_texture(texture, x, y)));
}

// Projette la texture sur le cylindre
t_rgb	get_texture_from_cylinder(t_vec3d pos, float r, t_data_img *texture)
{
    float theta;
    float phi;
    int x;
    int y;

    cartesian_to_spherical(pos, r, &theta, &phi);
    x = (int)(theta / (2 * M_PI) * texture->width);
    y = (int)((pos.z / (2 * r) + 0.5) * texture->height);
    return (int_to_rgb(get_color_from_texture(texture, x, y)));
}