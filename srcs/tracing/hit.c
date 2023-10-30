/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/30 08:19:01 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_hit(t_hit *hit)
{
	t_hit	*hit_next;

	while (hit)
	{
		hit_next = hit->next;
		free(hit);
		hit = hit_next;
	}
}

void	hit_redirect(t_ray ray, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_ray, t_obj *, t_hit *);

	ptr_ft[0] = &in_sp;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

void	get_hit(t_scenario *sc, t_ray ray, t_hit *hit)
{
	t_hit	hit_loc;
	t_obj	*obj;

	hit->dst = -1;
	hit_loc.dst = -1;
	obj = sc->obj;
	hit_loc.hit = false;
	hit->hit = false;
	hit->next = NULL;
	while (obj)
	{
		hit_redirect(ray, obj, &hit_loc);
		if (hit_loc.hit == true
			&& (hit->dst > hit_loc.dst || hit->hit == false))
		{
			free_hit(hit->next);
			hit->dst = hit_loc.dst;
			hit->pos = hit_loc.pos;
			hit->normal = hit_loc.normal;
			hit->rgb = hit_loc.rgb;
			hit->id = hit_loc.id;
			hit->hit = true;
		}
		if (hit_loc.hit == true
			&& (hit->dst == hit_loc.dst || hit->hit == false))
		obj = obj->next;
	}
}
