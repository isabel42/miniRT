/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:35:21 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/29 12:50:42 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation_ctrl_cam(t_scenario *scena)
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

void	apply_rotation_alt_cam(t_scenario *scena)
{
	int		i;
	t_vec3d	offset;
	i = 0;

	offset = v_quat_create(scena->view->camera[4]);
	while (i <= 4)
	{
		scena->view->camera[i] = quat_sub_offset(scena->view->camera[i], offset);
		scena->view->camera[i] = quat_multiply(
			quat_multiply(scena->view->rotation_quat, scena->view->camera[i]),
			quat_conjugate(scena->view->rotation_quat));
		scena->view->camera[i] = quat_add_offset(scena->view->camera[i], offset);
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

void	apply_rotation_axis_light(t_scenario *scena)
{
	int			i;
	t_spotlux	*obj;
	i = 0;

	obj = scena->spot_lux;
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
	apply_rotation_axis_light(scena);
}