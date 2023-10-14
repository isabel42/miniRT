/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/14 14:45:07 by itovar-n         ###   ########.fr       */
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

t_rgb	shadow_ray_rgb(t_ray ray, t_scenario *scena, t_hit object_hit)
{
	t_hit	hit;
	float	scale;

	hit.dst = -1.0000;
	get_hit(scena, ray, &hit, false);
	// printf("hit.dst: %f\n", hit.dst);
	if (hit.hit == false)
	{
		// printf("hit.dst: %f\n", hit.dst);
		scale = fmax(0.0, ft_dot(ft_normalize(object_hit.normal), ft_normalize(ft_v_sub(scena->spot_lux->pos, ray.origin))))
			* scena->spot_lux->ratio;
		if (scale > scena->amb_lux->ratio)
		{
			return (scale_color(object_hit.rgb, scale));
		}
	}
	return (scale_color(object_hit.rgb, scena->amb_lux->ratio));
}

void	shadow_ray_rgb_2(t_scenario *sc, t_hit hit, int i, int j)
{
	float	sl_new;
	float	amb_new;
	float	ratio;
	t_hit	hit_lux;
	t_ray	ray_lux;
	double	scale;
	t_rgb	rgb_final;

	ratio = fmax(1.0, sc->spot_lux->ratio + sc->amb_lux->ratio);
	sl_new = (sc->spot_lux->ratio / ratio) ;
	amb_new = (sc->amb_lux->ratio / ratio);
	ray_lux.origin = hit.pos;
	ray_lux.dir = ft_v_sub(sc->spot_lux->pos, hit.pos);

	hit_lux.hit = false;
	get_hit(sc, ray_lux, &hit_lux, false);
	scale = amb_new;
	if (hit_lux.hit == false)
		scale = sl_new * fmax(0.0, ft_dot(ft_normalize(hit.normal), ft_normalize(ft_v_sub(sc->spot_lux->pos, hit.pos)))) + scale;
	
	scale = scale * 1000;
	rgb_final.r = (hit.rgb.r * scale) /1000;
	rgb_final.g = (hit.rgb.g * scale) /1000;
	rgb_final.b = (hit.rgb.b * scale) /1000;

	my_mlx_pixel_put(sc->img_data, i, HEIGHT - j, rgb_to_int(rgb_final));
}
