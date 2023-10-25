/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:35:21 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/25 12:37:46 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation_o_cam(t_scenario *scena)
{
	int	i;

	i = 0;

	while (i <= 4)
	{
		// scena->view->camera[i] = quat_add_offset(scena->view->camera[i], scena->cam->pos);
		scena->view->camera[i] = quat_multiply(
			quat_multiply(scena->view->rotation_quat, scena->view->camera[i]),
			quat_conjugate(scena->view->rotation_quat));
		// scena->view->camera[i] = quat_sub_offset(scena->view->camera[i], scena->cam->pos);
		i++;
	}
}

void	apply_rotation_camera(t_scenario *scena)
{
	int	i;

	i = 0;

	while (i <= 4)
	{
		scena->view->camera[i] = quat_multiply(
			quat_multiply(scena->view->rotation_quat, scena->view->camera[i]),
			quat_conjugate(scena->view->rotation_quat));
		i++;
	}
}

void	apply_rotation_box(t_scenario *scena)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		scena->view->box[i] = quat_multiply(
			quat_multiply(scena->view->rotation_quat, scena->view->box[i]),
			quat_conjugate(scena->view->rotation_quat));
		i++;
	}
}

void	apply_rotation_axis(t_scenario *scena)
{
	int		i;
	t_obj	*obj;
	i = 0;

	obj = scena->obj;
	while (obj)
	{
		while (i <= 3)
		{
			obj->axis[i] = quat_multiply(
				quat_multiply(scena->view->rotation_quat, obj->axis[i]),
				quat_conjugate(scena->view->rotation_quat));
			i++;
		}
		i = 0;
		obj = obj->next;
	}
}


void	apply_rotation_scena(t_scenario *scena)
{
	apply_rotation_box(scena);
	apply_rotation_camera(scena);
	apply_rotation_axis(scena);
}