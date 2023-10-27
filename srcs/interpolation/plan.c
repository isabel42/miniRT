/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:13 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 14:39:45 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/*  https://www.kristakingmath.com/blog/intersection-of-a-ray-and-a-plane */
/**/

void	in_pl(t_ray ray, t_obj *pl, t_hit *hit)
{
	float	pl_sing;
	float	t;

	pl_sing = pl->dir.x * pl->pos.x
		+ pl->dir.y * pl->pos.y + pl->dir.z * pl->pos.z;
	if (ray.dir.x * pl->dir.x + ray.dir.y * pl->dir.y
		+ ray.dir.z * pl->dir.z == 0
		&& pl->dir.x * ray.origin.x + pl->dir.y * ray.origin.y
		+ pl->dir.z * ray.origin.z != pl_sing)
		return ;
	t = (pl_sing - ray.origin.x * pl->dir.x - ray.origin.y * pl->dir.y
			- ray.origin.z * pl->dir.z) / (ray.dir.x * pl->dir.x
			+ (ray.dir.y * pl->dir.y + ray.dir.z * pl->dir.z));
	if (t > 0.0001)
	{
		hit->pos.x = ray.origin.x + ray.dir.x * t;
		hit->pos.y = ray.origin.y + ray.dir.y * t;
		hit->pos.z = ray.origin.z + ray.dir.z * t;
		hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
		hit->normal = pl->dir;
		hit->rgb = pl->rgb;
		hit->hit = true;
		hit->id = 1;
	}
}

void	plane_hit(t_ray ray, t_obj *obj, t_hit *hit)
{
	float	denom;
	float	t;

	denom = ft_dot(obj->dir, ray.dir);
	if (fabsf(denom) > 1e-6)
	{
		t = ft_dot(ft_v_sub(obj->pos, ray.origin), obj->dir) / denom;
		if (t > 0.00001)
		{
			hit->hit = true;
			hit->dst = t;
			hit->pos = ft_v_add(ray.origin, ft_v_scale(ray.dir, t));
			hit->normal = obj->dir;
			hit->rgb = obj->rgb;
			hit->id = obj->id;
		}
	}
}