/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/13 17:47:08 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_rgbf
{
	float	r;
	float	g;
	float	b;
}				t_rgbf;

t_rgb	scale_color(t_rgb c, float scale)
{
	t_rgb result;

	result.r = c.r * scale;
	result.g = c.g * scale;
	result.b = c.b * scale;
	return (result);
}

t_rgb	mix_color(t_rgb color1, t_rgb color2, float scale)
{
	t_rgb	result;

	result.r = fmin(255, ((color1.r + (color2.r - color1.r) * scale) * scale));
	result.g = fmin(255, ((color1.g + (color2.g - color1.g) * scale) * scale));
	result.b = fmin(255, ((color1.b + (color2.b - color1.b) * scale) * scale));
	return (result);
}

t_rgb	mix_color_light(t_rgb object, t_rgb light, float scale)
{
	t_rgb	result;
	float	red;
	float	green;
	float	blue;

	red = (object.r / 255.0) * (light.r / 255.0) * scale * 255.0;
	green = (object.g / 255.0) * (light.g / 255.0) * scale * 255.0;
	blue = (object.b / 255.0) * (light.b / 255.0) * scale * 255.0;
	result.r = red;
	result.g = green;
	result.b = blue;
	return (result);
}

t_rgb	shadow_ray_rgb(t_ray ray, t_scenario *scena, t_hit object_hit)
{
	t_hit	hit;
	float	scale;

	hit.dst = -1.0000;
	get_hit(scena, ray, &hit);
	// printf("hit.dst: %f\n", hit.dst);
	if (hit.hit == false)
	{
		// printf("hit.dst: %f\n", hit.dst);
		scale = fmax(0.0, ft_dot(ft_normalize(object_hit.normal), ft_normalize(ft_v_sub(scena->spot_lux->pos, ray.origin)))) * scena->spot_lux->ratio;
		if (scale >= scena->amb_lux->ratio)
		{
			return (mix_color_light(object_hit.rgb, scena->spot_lux->rgb, scale));
		}
		// else
		// 	return (mix_color_light(object_hit.rgb, mix_color_light(scena->spot_lux->rgb, scena->amb_lux->rgb, scena->amb_lux->ratio), scale));
		// else
		// 	return (mix_color(object_hit.rgb, scena->amb_lux->rgb, scena->amb_lux->ratio));
		// return (int_to_rgb(I_YELLOW));
	}
	return (mix_color_light(object_hit.rgb, scena->amb_lux->rgb, scena->amb_lux->ratio));
}