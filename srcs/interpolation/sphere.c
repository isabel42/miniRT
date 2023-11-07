/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:32:39 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/07 11:47:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**/
/* https://paulbourke.net/geometry/circlesphere/index.html#raysphere */
/**/

void	cal_sp_param(t_vec3d *abc, t_ray ray, t_obj *sp)
{
	(*abc).x = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	(*abc).y = 2 * (ray.dir.x * (ray.origin.x - sp->pos.x)
			+ ray.dir.y * (ray.origin.y - sp->pos.y)
			+ ray.dir.z * (ray.origin.z - sp->pos.z));
	(*abc).z = pow(sp->pos.x, 2) + pow(sp->pos.y, 2) + pow(sp->pos.z, 2)
		+ pow(ray.origin.x, 2) + pow(ray.origin.y, 2) + pow(ray.origin.z, 2)
		- 2 * (sp->pos.x * ray.origin.x + sp->pos.y * ray.origin.y
			+ sp->pos.z * ray.origin.z) - pow(sp->diam / 2, 2);
}

void	in_sp_all(t_ray ray, t_obj *sp, t_hit *hit, float t)
{
	t_vec3d	sol2;

	if (t > 0.0001)
	{
		sol2.z = ray.origin.z + t * ray.dir.z;
		sol2.y = ray.origin.y + t * ray.dir.y;
		sol2.x = ray.origin.x + t * ray.dir.x;
		if (hit->dst > ft_mod(ft_v_sub(sol2, ray.origin)) || hit->hit == false)
		{
			hit->pos.z = ray.origin.z + t * ray.dir.z;
			hit->pos.y = ray.origin.y + t * ray.dir.y;
			hit->pos.x = ray.origin.x + t * ray.dir.x;
			hit->dst = ft_mod(ft_v_sub(sol2, ray.origin));
			hit->normal = ft_v_sub(hit->pos, sp->pos);
			if (ft_dot(ray.dir, hit->normal) > 0.000)
				hit->normal = ft_v_scale(hit->normal, -1.0);
			hit->rgb = sp->rgb;
			hit->hit = true;
			hit->id = 0;
			if (sp->texture)
				hit->rgb = get_texture_from_sphere(
						ft_v_sub((*hit).pos,
							(*sp).pos), sp->diam / 2, sp->texture);
		}
	}
}

void	in_sp(t_ray ray, t_obj *sp, t_hit *hit)
{
	t_vec3d	abc;
	float	sq;

	cal_sp_param(&abc, ray, sp);
	sq = powf(abc.y, 2) - 4 * abc.x * abc.z;
	if (sq < 0 || (sq == 0 && abc.x == 0))
		return ;
	in_sp_all(ray, sp, hit, (-abc.y - sqrt(sq)) / (2 * abc.x));
	in_sp_all(ray, sp, hit, (-abc.y + sqrt(sq)) / (2 * abc.x));
}
