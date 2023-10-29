/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:10:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 10:12:56 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_tracing
{
	int	i;
	int	j;
	int	d;
}				t_tracing;

t_vec3d	quat_to_point(t_quat q)
{
	t_vec3d	res;

	res.x = q.x;
	res.y = q.y;
	res.z = q.z;
	return (res);
}

t_tracing	init_tracing(t_scenario *sc)
{
	t_tracing	t;

	if (sc->cam->fov == 180)
		t.d = 0;
	else
		t.d = tan(ft_deg_to_rad(sc->cam->fov / 2)) * WIDTH / 2;
	t.i = 0;
	t.j = 0;
	return (t);
}

t_ray	init_ray(t_scenario *sc, t_tracing t)
{
	t_ray	ray;

	ray.dir = quat_v_transform(sc->cam->dir, (t_vec3d){t.i - WIDTH / 2, t.j - HEIGHT / 2, t.d});
	ray.origin = sc->cam->pos;
	return (ray);
}

void	tracing(t_scenario *sc)
{
	t_tracing	t;
	t_hit		hit;
	t_ray		ray;
	// t_ray		ray_lux;

	t = init_tracing(sc);
	while (t.i <= WIDTH)
	{
		t.j = 0;
		while (t.j <= HEIGHT)
		{
			ray = init_ray(sc, t);
			get_hit(sc, ray, &hit, false);
			if (hit.hit == true)
			{
				shadow_ray_rgb(sc, hit, t.i, t.j);
				// ray_lux.origin = hit.pos;
				// ray_lux.dir = ft_v_sub(sc->spot_lux->pos, hit.pos);
				// // my_mlx_pixel_put(sc->img_data, t.i, HEIGHT - t.j, rgb_to_int(hit.rgb));
				// my_mlx_pixel_put(sc->img_data, t.i, HEIGHT - t.j, rgb_to_int(shadow_ray_rgb(ray_lux, sc, hit)));
			}
			t.j++;
		}
		t.i++;
	}
}
