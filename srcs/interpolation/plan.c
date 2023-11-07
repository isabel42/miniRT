/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:33:13 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/07 11:58:10 by lsohler          ###   ########.fr       */
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

	pl_sing = ft_dot(pl->dir, pl->pos);
	if (!ft_dot(ray.dir, pl->dir) && ft_dot(pl->dir, ray.origin) != pl_sing)
		return ;
	t = (pl_sing - ft_dot(pl->dir, ray.origin)) / (ft_dot(ray.dir, pl->dir));
	if (t > 0.0001)
	{
		hit->pos.x = ray.origin.x + ray.dir.x * t;
		hit->pos.y = ray.origin.y + ray.dir.y * t;
		hit->pos.z = ray.origin.z + ray.dir.z * t;
		hit->dst = ft_mod(ft_v_sub(hit->pos, ray.origin));
		hit->normal = pl->dir;
		if (!fmax(0.0, ft_dot(ft_normalize(pl->dir),
					ft_normalize(ft_v_sub(ray.origin, hit->pos)))))
			hit->normal = ft_v_scale(hit->normal, -1.0);
		hit->rgb = pl->rgb;
		hit->hit = true;
		hit->id = 1;
		if (pl->texture && pl->id == PL)
			hit->rgb = rgb_scale_from_ref(get_texture_from_plane(
						hit->pos, hit->normal, pl->texture), pl->rgb);
	}
}
