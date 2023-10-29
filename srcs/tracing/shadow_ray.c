/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 19:20:53 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	scale_color(t_rgb c, float scale)
{
	t_rgb	result;

	result.r = c.r * scale;
	result.g = c.g * scale;
	result.b = c.b * scale;
	return (result);
}

float	get_ratio_shadow(t_scenario *sc)
{
	float		*ratio;
	float		sol;
	t_spotlux	*spot;

	spot = sc->spot_lux;
	ratio = malloc (sizeof(float) * 3);
	if (!ratio)
		ft_exit("Malloc");
	ratio[0] = sc->amb_lux->ratio * sc->amb_lux->rgb.r / 255;
	ratio[1] = sc->amb_lux->ratio * sc->amb_lux->rgb.g / 255;
	ratio[2] = sc->amb_lux->ratio * sc->amb_lux->rgb.b / 255;
	while (spot)
	{
		ratio[0] = spot->ratio * spot->rgb.r / 255 + ratio[0];
		ratio[1] = spot->ratio * spot->rgb.g / 255 + ratio[1];
		ratio[2] = spot->ratio * spot->rgb.b / 255 + ratio[2];
		spot = spot->next;
	}
	ratio[0] = fmax(1.0, ratio[0]);
	ratio[1] = fmax(1.0, ratio[1]);
	ratio[2] = fmax(1.0, ratio[2]);
	sol = fmax(ratio[0], ratio[1]);
	sol = fmax(ratio[2], sol);
	free (ratio);
	return (sol);
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

void	get_scale_shadow(t_scenario *sc, t_hit hit, double *scale)
{
	t_hit		hit_lux;
	t_ray		ray_lux;
	t_spotlux	*spot;
	double		cos;

	ray_lux.origin = hit.pos;
	scale[0] = sc->amb_lux->ratio_norm * sc->amb_lux->rgb.r / 255;
	scale[1] = sc->amb_lux->ratio_norm * sc->amb_lux->rgb.g / 255;
	scale[2] = sc->amb_lux->ratio_norm * sc->amb_lux->rgb.b / 255;
	spot = sc->spot_lux;
	while (spot)
	{
		ray_lux.dir = ft_v_sub(spot->pos, hit.pos);
		hit_lux.hit = false;
		hit_lux.dst = -1;
		get_hit(sc, ray_lux, &hit_lux, false);
		if (hit_lux.hit == false || hit_lux.dst > ft_mod(ft_v_sub(spot->pos, hit.pos)))
		{
		// printf("hit_lux.dst: %f\tft_mod(ft_v_sub(spot->pos, hit.pos)): %f\n", );
			cos = fmax(0.00000, ft_dot(ft_normalize(hit.normal),
						ft_normalize(ray_lux.dir)));
			scale[0] = spot->ratio_norm * cos * spot->rgb.r / 255 + scale[0];
			scale[1] = spot->ratio_norm * cos * spot->rgb.g / 255 + scale[1];
			scale[2] = spot->ratio_norm * cos * spot->rgb.b / 255 + scale[2];
		}
		spot = spot->next;
	}
}

void	shadow_ray_rgb(t_scenario *sc, t_hit hit, int i, int j)
{
	float	ratio;
	double	*scale;
	t_rgb	rgb_final;

	ratio = get_ratio_shadow(sc);
	set_ratio_norm(sc, ratio);
	scale = malloc(sizeof(double) * 3);
	if (!scale)
		ft_exit("Malloc");
	get_scale_shadow(sc, hit, scale);
	rgb_final.r = (hit.rgb.r * scale[0]);
	rgb_final.g = (hit.rgb.g * scale[1]);
	rgb_final.b = (hit.rgb.b * scale[2]);
	my_mlx_pixel_put(sc->img_data, i, HEIGHT - j, rgb_to_int(rgb_final));
	free(scale);
}
