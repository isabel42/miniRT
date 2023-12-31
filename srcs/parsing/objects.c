/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:35:41 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/11 17:20:36 by lsohler          ###   ########.fr       */
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
	sph->cube = init_cube(sph->pos, sph->diam);
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
	pln->dir = ft_pos(split[2]);
	pln->rgb = ft_rgb(split[3]);
	pln->cube = init_cube(pln->pos, 20.0);
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
	cyl->cube = init_cube(cyl->pos, 20.0);
	cyl->next = NULL;
	free_array(split);
	object_add_back(scena, cyl);
}
