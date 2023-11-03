/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:20 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/03 12:41:09 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_rotation_ctrl_cam(t_scenario *scena)
{
	int	i;

	i = 0;
	while (i <= 4)
	{
		scena->view->camera[i] = quat_multiply(
				quat_multiply(scena->view->rotation_quat,
					scena->view->camera[i]),
				quat_conjugate(scena->view->rotation_quat));
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
		scena->view->camera[i] = quat_sub_offset(
				scena->view->camera[i], offset);
		scena->view->camera[i] = quat_multiply(
				quat_multiply(scena->view->rotation_quat,
					scena->view->camera[i]),
				quat_conjugate(scena->view->rotation_quat));
		scena->view->camera[i] = quat_add_offset(
				scena->view->camera[i], offset);
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
				quat_multiply(scena->view->rotation_quat,
					scena->view->camera[i]),
				quat_conjugate(scena->view->rotation_quat));
		i++;
	}
}
