/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:00 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 14:40:15 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/* https://www.youtube.com/watch?v=IKQCtqvGTJM */
/**/

void	in_cn_body(t_ray ray, t_obj *cn, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0.0001)
	{
		sol2.x = ray.origin.x + t * ray.dir.x;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.z = ray.origin.z + t * ray.dir.z;
		if ((hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
			&& !fmax(ft_dot(ft_normalize(ft_v_sub(sol2, cn->pos)), ft_normalize(cn->dir)), 0.00)
			&& ft_dot(ft_v_sub(sol2, cn->pos), cn->dir) > - cn->high)
		{
			hit->pos = sol2;
			hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
			hit->normal = vct_orto(ft_v_sub(hit->pos, cn->pos), cn->dir);
			hit->normal = vct_orto(hit->normal, ft_v_sub(hit->pos, cn->pos));
			if (ft_dot(ray.dir, hit->normal) > 0.000)
				hit->normal = ft_fv_mul(-1.0, hit->normal);
			hit->rgb = cn->rgb;
			hit->hit = true;
			hit->id = 2;
		}
	}
}

// void	in_cn_caps(t_ray ray, t_obj *cn, t_hit *hit, float t)
// {
// 	t_obj	cap;
// 	t_hit	hit_loc;

// 	cap.dir = cn->dir;
// 	cap.pos.x = cn->pos.x + t * cn->dir.x;
// 	cap.pos.y = cn->pos.y + t * cn->dir.y;
// 	cap.pos.z = cn->pos.z + t * cn->dir.z;
// 	in_pl(ray, &cap, &hit_loc);
// 	if (hit_loc.hit == true && (hit->dst > hit_loc.dst || hit->hit == false)
// 		&& ft_mod(ft_v_sub(hit_loc.pos, cap.pos)) <= cn->diam / 2)
// 	{
// 		hit->pos = hit_loc.pos;
// 		hit->dst = hit_loc.dst;
// 		hit->normal = cn->dir;
// 		hit->rgb = cn->rgb;
// 		hit->hit = true;
// 		hit->id = 2;
// 	}
// }

void	in_cn(t_ray ray, t_obj *cn, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;
	float	k;

	k = cn->diam / (2 * cn->high);
	cal_cn_param(&abc, ray, cn, k);
	sq = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (sq < 0 || !abc.x)
		return ;
	in_cn_body(ray, cn, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
	in_cn_body(ray, cn, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
	// in_cn_caps(ray, cn, hit, (cn->high / 2) / ft_mod(cn->dir));
	// in_cn_caps(ray, cn, hit, -(cn->high / 2) / ft_mod(cn->dir));
}
