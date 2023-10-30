/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/30 15:17:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	get_cos_lux_hit(t_hit hit, t_ray ray_lux)
{
	double		cos;
	double		cos_final;

	cos_final = 1.000;
	while (42)
	{
		cos = fmax(0.00000, ft_dot(ft_normalize(hit.normal),
					ft_normalize(ray_lux.dir)));
		cos_final = fmin(cos, cos_final);
		if (hit.next == NULL || hit.dst < hit.next->dst)
			break ;
		hit = *(hit.next);
	}
	return (cos_final);
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
		get_hit(sc, ray_lux, &hit_lux);
		if (hit_lux.hit == false
			|| ft_mod(ft_v_sub(hit_lux.pos, hit.pos))
			> ft_mod(ft_v_sub(spot->pos, hit.pos)))
		{
			cos = get_cos_lux_hit(hit, ray_lux);
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
