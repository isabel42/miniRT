/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/10/24 12:32:05 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_spot(t_scenario *scena)
{
	t_spotlux	*tmp;

	while (scena->spot_lux)
	{
		tmp = scena->spot_lux->next;
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
		free(scena->obj);
		scena->obj = tmp;
	}
}

void	free_scenario(t_scenario *scena)
{
	if (scena->amb_lux)
		free(scena->amb_lux);
	if (scena->cam)
		free(scena->cam);
	if (scena->mlx)
		free(scena->mlx);
	if (scena->img_data)
		free(scena->img_data);
	if (scena->view->mlx)
		free(scena->view->mlx);
	if (scena->view->img_data)
		free(scena->view->img_data);
	free_obj(scena);
	free_spot(scena);
}
