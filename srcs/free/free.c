/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/11/06 14:56:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_hit(t_hit **hit_list)
{
	t_hit	*hit;
	t_hit	*hit_next;

	hit = *hit_list;
	while (hit)
	{
		hit_next = hit->next;
		free(hit);
		hit = hit_next;
	}
}

void	free_spot(t_scenario *scena)
{
	t_spotlux	*tmp;

	while (scena->spot_lux)
	{
		tmp = scena->spot_lux->next;
		free(scena->spot_lux->axis);
		free(scena->spot_lux);
		scena->spot_lux = tmp;
	}
}

void	free_obj(t_scenario	*scena)
{
	t_obj	*tmp;

	while (scena->obj)
	{
		tmp = scena->obj->next;
		free(scena->obj->axis);
		free(scena->obj);
		scena->obj = tmp;
	}
}

void	free_texture_list(t_scenario *scena)
{
	t_texture_list	*tmp;

	while (scena->textures)
	{
		tmp = scena->textures->next;
		if (scena->textures->texture_name)
			free(scena->textures->texture_name);
		if (scena->textures->texture)
			free(scena->textures->texture);
		free(scena->textures);
		scena->textures = tmp;
	}
}

void	free_scenario(t_scenario *scena)
{
	if (scena->view->img_data)
		free(scena->view->img_data);
	if (scena->view->mlx)
		free(scena->view->mlx);
	if (scena->amb_lux)
		free(scena->amb_lux);
	if (scena->cam)
		free(scena->cam);
	if (scena->view->camera)
		free(scena->view->camera);
	if (scena->view->box)
		free(scena->view->box);
	if (scena->view)
		free(scena->view);
	free_obj(scena);
	free_spot(scena);
	if (scena->textures)
		free_texture_list(scena);
}
