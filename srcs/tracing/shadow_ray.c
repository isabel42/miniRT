/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/11 16:34:52 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	scale_color(t_rgb c, float scale)
{
	t_rgb result;

	result.r = c.r * scale;
	result.g = c.g * scale;
	result.b = c.b * scale;
	return (result);
}

t_rgb	shadow_ray_rgb(t_vec3d p1, t_vec3d p2, t_scenario *scena, t_hit object_hit)
{
	t_hit	hit;
	float	scale;

	get_hit(scena, &p1, &p2, &hit);
	if (hit.dst >= -1 && (object_hit.dst < hit.dst && object_hit.dst > 0))
	{
		scale = fmax(0.0, ft_dot(ft_normalize(object_hit.normal), ft_normalize(ft_v_sub(p2, p1))))
			* scena->spot_lux->ratio;
		if (scale > 0)
			printf("scale: %f\n", scale);
		if (scale > scena->amb_lux->ratio)
		{
			return (scale_color(object_hit.rgb, scale));
		}
	}
	return (scale_color(object_hit.rgb, scena->amb_lux->ratio));
}