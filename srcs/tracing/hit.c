/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/27 15:34:31 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_redirect(t_ray ray, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_ray, t_obj *, t_hit *);

	ptr_ft[0] = &sphere_hit;
	ptr_ft[1] = &plane_hit;
	ptr_ft[2] = &cylinder_hit;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

void	get_hit(t_scenario *sc, t_ray ray, t_hit *hit, bool stop_first)
{
	t_hit	hit_loc;
	t_obj	*obj;

	hit->dst = -1;
	hit_loc.dst = -1;
	obj = sc->obj;
	hit_loc.hit = false;
	hit->hit = false;
	while (obj)
	{
		hit_redirect(ray, obj, &hit_loc);
		if (hit_loc.hit == true
			&& (hit->dst > hit_loc.dst || hit->hit == false))
		{
			hit->dst = hit_loc.dst;
			hit->pos = hit_loc.pos;
			hit->normal = hit_loc.normal;
			hit->rgb = hit_loc.rgb;
			hit->id = hit_loc.id;
			hit->hit = true;
			if (stop_first == true)
				break ;
		}
		obj = obj->next;
	}
}
