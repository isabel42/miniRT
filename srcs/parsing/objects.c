/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:35:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/11/01 13:18:23 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	object_add_back(t_scenario *scena, t_obj *object)
{
	t_obj	*list;

	list = scena->obj;
	if (!list)
		scena->obj = object;
	else
	{
		while (list->next)
			list = list->next;
		list->next = object;
	}
}

void	new_sphere(char **split, t_scenario *scena)
{
	t_obj	*sph;

	if (!split || !split[3] || split[4])
		ft_exit("Sphere syntax");
	sph = malloc(sizeof (t_obj));
	if (!sph)
		ft_exit("Malloc");
	sph->id = sp;
	sph->high = 0;
	sph->pos = ft_pos(split[1]);
	sph->diam = ft_atof(split[2]);
	sph->rgb = ft_rgb(split[3]);
	sph->next = NULL;
	free_array(split);
	object_add_back(scena, sph);
}

void	new_plan(char **split, t_scenario *scena)
{
	t_obj	*pln;

	if (!split || !split[3] || split[4])
		ft_exit("Plan syntax");
	pln = malloc(sizeof (t_obj));
	if (!pln)
		ft_exit("Malloc");
	pln->id = pl;
	pln->diam = 0;
	pln->high = 0;
	pln->pos = ft_pos(split[1]);
	pln->dir = get_orientation(split[2], -1.0, 1.0);
	pln->rgb = ft_rgb(split[3]);
	pln->next = NULL;
	free_array(split);
	object_add_back(scena, pln);
}

void	new_cylinder(char **split, t_scenario *scena)
{
	t_obj	*cyl;

	if (!split || !split[5] || split[6])
		ft_exit("Cylinder syntax");
	cyl = malloc(sizeof (t_obj));
	if (!cyl)
		ft_exit("Malloc");
	cyl->id = cy;
	cyl->pos = ft_pos(split[1]);
	cyl->dir = ft_pos(split[2]);
	cyl->diam = ft_atof(split[3]);
	cyl->high = ft_atof(split[4]);
	cyl->rgb = ft_rgb(split[5]);
	cyl->next = NULL;
	free_array(split);
	object_add_back(scena, cyl);
}

void	new_cone(char **split, t_scenario *scena)
{
	t_obj	*cn;

	if (!split || !split[5] || split[6])
		ft_exit("Cone syntax");
	cn = malloc(sizeof (t_obj));
	if (!cn)
		ft_exit("Malloc");
	cn->id = cne;
	cn->pos = ft_pos(split[1]);
	cn->dir = ft_pos(split[2]);
	cn->diam = ft_atof(split[3]);
	cn->high = ft_atof(split[4]);
	cn->rgb = ft_rgb(split[5]);
	cn->next = NULL;
	free_array(split);
	object_add_back(scena, cn);
}
