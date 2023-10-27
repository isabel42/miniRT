/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:18:44 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 15:25:09 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
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
		get_hit(sc, ray_lux, &hit_lux, false);
		if (hit_lux.hit == false)
		{
			cos = fmax(0.0, ft_dot(ft_normalize(hit.normal),
						ft_normalize(ft_v_sub(spot->pos, hit.pos))));
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
	// my_mlx_pixel_put(sc->img_data, i, j, rgb_to_int(hit.rgb));
	free(scale);
}*/
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
	get_hit(scena, ray, &hit, false);
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