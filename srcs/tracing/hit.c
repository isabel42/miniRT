/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:15:38 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/01 19:11:48 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_add_back(t_hit **list, t_hit *hit_add)
{
	t_hit	*hit;

	hit = *list;
	if (!hit)
		hit = hit_add;
	else
	{
		while (hit->next)
			hit = hit->next;
		hit->next = hit_add;
	}
}

void	hit_redirect(t_ray ray, t_obj *obj, t_hit *hit_loc)
{
	void	(*ptr_ft[4])(t_ray, t_obj *, t_hit *);

	ptr_ft[0] = &in_sp;
	ptr_ft[1] = &in_pl;
	ptr_ft[2] = &in_cy;
	ptr_ft[3] = &in_cn;
	ptr_ft[obj->id](ray, obj, hit_loc);
}

void	cp_hit(t_hit *hit_to, t_hit hit_from)
{
	hit_to->dst = hit_from.dst;
	hit_to->pos = hit_from.pos;
	hit_to->normal = hit_from.normal;
	hit_to->rgb = hit_from.rgb;
	hit_to->id = hit_from.id;
	hit_to->hit = hit_from.hit;
	hit_to->next = NULL;
}

void	hit_equal(t_hit **hit_list, t_hit hit_loc)
{
	t_hit	*hit_add;

	hit_add = malloc(sizeof(t_hit));
	if (!hit_add)
		ft_exit("Malloc");
	cp_hit(hit_add, hit_loc);
	hit_add_back(hit_list, hit_add);
}

void	get_hit(t_scenario *sc, t_ray ray, t_hit *hit)
{
	t_hit	hit_loc;
	t_obj	*obj;

	hit->next = NULL;
	hit->dst = -1;
	obj = sc->obj;
	hit->hit = false;
	while (obj)
	{
		hit_loc.hit = false;
		hit_loc.dst = -1;
		hit_redirect(ray, obj, &hit_loc);
		if (hit_loc.hit == true
			&& (hit->dst > hit_loc.dst || hit->hit == false))
		{
			free_hit(&(hit->next));
			cp_hit(hit, hit_loc);
		}
		else if (hit_loc.hit == true && hit->dst == hit_loc.dst)
			hit_equal(&hit, hit_loc);
		obj = obj->next;
	}
}
