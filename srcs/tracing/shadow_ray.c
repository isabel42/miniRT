/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/15 15:27:01 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_ratio_shadow(t_scenario *sc)
{
	float		ratio;
	t_spotlux	*spot;

	spot = sc->spot_lux;
	ratio = sc->amb_lux->ratio;
	while (spot)
	{
		ratio = ratio + sc->spot_lux->ratio;
		spot = spot->next;
	}
	ratio = fmax(1.0, ratio);
	return (ratio);
}

void	set_ratio_norm(t_scenario *sc, float ratio)
{
	t_spotlux	*spot;

	spot = sc->spot_lux;
	while (spot)
	{
		spot->ratio_norm = (spot->ratio / ratio);
		spot = spot->next;
	}
	sc->amb_lux->ratio_norm = (sc->amb_lux->ratio / ratio);
}

double	get_scale_shadow(t_scenario *sc, t_hit hit)
{
	t_hit		hit_lux;
	t_ray		ray_lux;
	t_spotlux	*spot;
	double		scale;

	ray_lux.origin = hit.pos;
	scale = sc->amb_lux->ratio_norm;
	spot = sc->spot_lux;
	while (spot)
	{
		ray_lux.dir = ft_v_sub(spot->pos, hit.pos);
		hit_lux.hit = false;
		get_hit(sc, ray_lux, &hit_lux, false);
		if (hit_lux.hit == false)
			scale = spot->ratio_norm * fmax(0.0,
					ft_dot(ft_normalize(hit.normal),
						ft_normalize(ft_v_sub(spot->pos, hit.pos)))) + scale;
		spot = spot->next;
	}
	scale = scale * 1000;
	return (scale);
}

void	shadow_ray_rgb(t_scenario *sc, t_hit hit, int i, int j)
{
	float	ratio;
	double	scale;
	t_rgb	rgb_final;

	ratio = get_ratio_shadow(sc);
	set_ratio_norm(sc, ratio);
	scale = get_scale_shadow(sc, hit);
	rgb_final.r = (hit.rgb.r * scale) / 1000;
	rgb_final.g = (hit.rgb.g * scale) / 1000;
	rgb_final.b = (hit.rgb.b * scale) / 1000;
	my_mlx_pixel_put(sc->img_data, i, HEIGHT - j, rgb_to_int(rgb_final));
}
