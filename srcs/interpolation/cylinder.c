/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:45:05 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/* https://www.youtube.com/watch?v=IKQCtqvGTJM */
/**/

t_vec3d	vct_orto(t_vec3d a, t_vec3d b)
{
	t_vec3d	sol;

	sol.x = a.y * b.z - a.z * b.y;
	sol.y = a.z * b.x - a.x * b.z;
	sol.z = a.x * b.y - a.y * b.x;
	return (sol);
}

void	in_cy_body(t_ray ray, t_obj *cy, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0.0001)
	{
		sol2.x = ray.origin.x + t * ray.dir.x;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.z = ray.origin.z + t * ray.dir.z;
		if ((hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
			&& powf(ft_mod(ft_v_sub(sol2, cy->pos)), 2) - powf(cy->diam / 2, 2)
			<= powf(cy->high / 2, 2))
		{
			hit->pos = sol2;
			hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
			hit->normal = vct_orto(ft_v_sub(hit->pos, cy->pos), cy->dir);
			hit->normal = vct_orto(hit->normal, cy->dir);
			if (ft_dot(ray.dir, hit->normal) > 0.000)
				hit->normal = ft_v_scale(hit->normal, -1.0);
			hit->rgb = cy->rgb;
			hit->hit = true;
			hit->id = 2;
		}
	}
}

void	in_cy_caps(t_ray ray, t_obj *cy, t_hit *hit, float t)
{
	t_obj	cap;
	t_hit	hit_loc;

	cap.dir = cy->dir;
	cap.pos.x = cy->pos.x + t * cy->dir.x;
	cap.pos.y = cy->pos.y + t * cy->dir.y;
	cap.pos.z = cy->pos.z + t * cy->dir.z;
	in_pl(ray, &cap, &hit_loc);
	if (hit_loc.hit == true && (hit->dst > hit_loc.dst || hit->hit == false)
		&& ft_mod(ft_v_sub(hit_loc.pos, cap.pos)) <= cy->diam / 2)
	{
		hit->pos = hit_loc.pos;
		hit->dst = hit_loc.dst;
		hit->normal = cy->dir;
		hit->rgb = cy->rgb;
		hit->hit = true;
		hit->id = 2;
	}
}

void	in_cy(t_ray ray, t_obj *cy, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;

	cal_cy_param(&abc, ray, cy);
	sq = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (sq < 0 || !abc.x)
		return ;
	in_cy_body(ray, cy, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
	in_cy_body(ray, cy, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
	in_cy_caps(ray, cy, hit, (cy->high / 2) / ft_mod(cy->dir));
	in_cy_caps(ray, cy, hit, -(cy->high / 2) / ft_mod(cy->dir));
}
