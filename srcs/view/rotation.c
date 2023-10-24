/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:35:21 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/24 18:42:14 by lsohler          ###   ########.fr       */
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
	scena->cam->pos.x = scena->view->camera[4].x;
	scena->cam->pos.y = -scena->view->camera[4].y;
	scena->cam->pos.z = -scena->view->camera[4].z;
}

void	apply_rotation_camera(t_scenario *scena)
{
	int	i;

	i = 0;

	while (i <= 4)
	{
		scena->view->camera[i] = quat_multiply(
			quat_multiply(scena->view->scena_quat, scena->view->camera[i]),
			quat_conjugate(scena->view->scena_quat));
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
			quat_multiply(scena->view->scena_quat, scena->view->box[i]),
			quat_conjugate(scena->view->scena_quat));
		i++;
	}
}

void	apply_rotation_axis(t_scenario *scena)
{
	int	i;

	i = 0;

	while (i <= 3)
	{
		scena->view->box[i] = quat_multiply(
			quat_multiply(scena->view->scena_quat, scena->view->box[i]),
			quat_conjugate(scena->view->scena_quat));
		i++;
	}
}


void	apply_rotation_scena(t_scenario *scena)
{
	apply_rotation_box(scena);
	apply_rotation_camera(scena);
	// apply_rotation_axis(scena);
}