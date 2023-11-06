/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/06 15:08:47 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/* https://www.youtube.com/watch?v=IKQCtqvGTJM */
/**/

void	in_cn_body(t_ray ray, t_obj *cn, t_hit *hit, float t)
{
	t_vec3d	sol2;
	t_vec3d	d;
	float	cos;

	if (t > 0.0001)
	{
		sol2.x = ray.origin.x + t * ray.dir.x;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.z = ray.origin.z + t * ray.dir.z;
		d = ft_v_sub(sol2, cn->pos);
		cos = ft_dot(ft_normalize(d), ft_normalize(cn->dir));
		if ((hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
			&& !fmax(cos, 0.00) && ft_mod(d) * cos > -cn->high)
		{
			hit->pos = sol2;
			hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
			hit->normal = ft_v_cprod(ft_v_sub(hit->pos, cn->pos), cn->dir);
			hit->normal = ft_v_cprod(hit->normal, ft_v_sub(hit->pos, cn->pos));
			if (ft_dot(ray.dir, hit->normal) > 0.000)
				hit->normal = ft_v_scale(hit->normal, -1.0);
			hit->rgb = cn->rgb;
			hit->hit = true;
			hit->id = cne_;
		}
	}
}

void	in_cn_caps(t_ray ray, t_obj *cn, t_hit *hit, float t)
{
	t_obj	cap;
	t_hit	hit_loc;

	cap.dir = cn->dir;
	cap.pos.x = cn->pos.x + t * cn->dir.x;
	cap.pos.y = cn->pos.y + t * cn->dir.y;
	cap.pos.z = cn->pos.z + t * cn->dir.z;
	in_pl(ray, &cap, &hit_loc);
	if (hit_loc.hit == true && (hit->dst > hit_loc.dst || hit->hit == false)
		&& ft_mod(ft_v_sub(hit_loc.pos, cap.pos)) <= cn->diam / 2)
	{
		hit->pos = hit_loc.pos;
		hit->dst = hit_loc.dst;
		hit->normal = cn->dir;
		hit->rgb = cn->rgb;
		hit->hit = true;
		hit->id = cne_;
	}
}

void	in_cn(t_ray ray, t_obj *cn, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;

	cal_cn_param(&abc, ray, cn);
	sq = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (sq < 0 || !abc.x)
		return ;
	in_cn_body(ray, cn, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
	in_cn_body(ray, cn, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
	in_cn_caps(ray, cn, hit, -(cn->high) / ft_mod(cn->dir));
}
