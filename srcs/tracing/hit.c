/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/30 15:35:36 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_redirect(t_ray ray, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_ray, t_obj *, t_hit *);

	ptr_ft[0] = &in_sp;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

void	cp_hit(t_hit *hit_to, t_hit hit_from)
{
	hit_to->dst = hit_from.dst;
	hit_to->pos = hit_from.pos;
	hit_to->normal = hit_from.normal;
	hit_to->rgb = hit_from.rgb;
	hit_to->id = hit_from.id;
	hit_to->hit = true;
}

void	hit_equal(t_hit *hit, t_hit hit_loc)
{
	hit->next = malloc(sizeof(t_hit));
	if (!hit->next)
		ft_exit("Malloc");
	hit = hit->next;
	cp_hit(hit, hit_loc);
	hit->next = NULL;
}

void	get_hit(t_scenario *sc, t_ray ray, t_hit *hit)
{
	t_hit	hit_loc;
	t_hit	*hit_first;
	t_obj	*obj;

	hit->dst = -1;
	hit_loc.dst = -1;
	obj = sc->obj;
	hit_loc.hit = false;
	hit->hit = false;
	hit_first = hit;
	hit->next = NULL;
	while (obj)
	{
		hit_redirect(ray, obj, &hit_loc);
		if (hit_loc.hit == true && hit->dst == hit_loc.dst)
			hit_equal(hit, hit_loc);
		else if (hit_loc.hit == true
			&& (hit->dst > hit_loc.dst || hit->hit == false))
		{
			hit = hit_first;
			cp_hit(hit, hit_loc);
		}
		obj = obj->next;
	}
}
