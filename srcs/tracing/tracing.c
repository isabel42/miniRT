/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:10:10 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 15:12:41 by itovar-n         ###   ########.fr       */
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
		t.d = (WIDTH / 2.0) / tan(ft_deg_to_rad(sc->cam->fov / 2.00));
	t.i = 0;
	t.j = 0;
	return (t);
}

t_ray	init_ray(t_scenario *sc, t_tracing t)
{
	t_ray	ray;
	t_vec3d	p2;
	t_quat	pq2;

	pq2 = quat_create(0, t.i - WIDTH / 2, t.j - HEIGHT / 2, t.d);
	pq2.w = 1;
	pq2 = quat_multiply(
			quat_multiply((sc->cam->dir), pq2),
			quat_conjugate((sc->cam->dir)));
	p2 = quat_to_point(pq2);
	p2 = ft_v_add(p2, sc->cam->pos);
	ray.dir = ft_v_sub(p2, sc->cam->pos);
	ray.origin = sc->cam->pos;
	return (ray);
}

void	tracing(t_scenario *sc)
{
	t_tracing	t;
	t_hit		hit;
	t_ray		ray;

	t = init_tracing(sc);
	while (t.i <= WIDTH)
	{
		t.j = 0;
		if (!(t.j + t.j + t.d))
			t.d = 1;
		while (t.j <= HEIGHT)
		{
			ray = init_ray(sc, t);
			get_hit(sc, ray, &hit);
			if (hit.hit == true)
			{
				shadow_ray_rgb(sc, hit, t.i, t.j);
				free_hit(&(hit.next));
			}
			t.j++;
		}
		t.i++;
	}
}
