/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:52:31 by lsohler           #+#    #+#             */
/*   Updated: 2023/10/08 16:20:17 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat	*init_cube(t_vec3d center, float size)
{
	float	half_size;
	t_quat	*cube;

	cube = malloc(sizeof(t_quat) * 8);
	if (!cube)
		ft_exit("Malloc");
	half_size = size / 2;
	printf("-------NEW CUBE------\n");
	cube[0] = quat_create(0, center.x - half_size, center.y - half_size, center.z - half_size);
	cube[1] = quat_create(0, center.x - half_size, center.y - half_size, center.z + half_size);
	cube[2] = quat_create(0, center.x - half_size, center.y + half_size, center.z + half_size);
	cube[3] = quat_create(0, center.x - half_size, center.y + half_size, center.z - half_size);
	cube[4] = quat_create(0, center.x + half_size, center.y - half_size, center.z - half_size);
	cube[5] = quat_create(0, center.x + half_size, center.y - half_size, center.z + half_size);
	cube[6] = quat_create(0, center.x + half_size, center.y + half_size, center.z + half_size);
	cube[7] = quat_create(0, center.x + half_size, center.y + half_size, center.z - half_size);
	return (cube);
}


t_quat	*init_axis(t_vec3d center, float size)
{
	t_quat	*axis;

	axis = malloc(sizeof(t_quat) * 8);
	if (!axis)
		ft_exit("Malloc");
	axis[0] = quat_create(0, center.x, center.y, center.z);
	axis[1] = quat_create(0, center.x + size, center.y, center.z);
	axis[2] = quat_create(0, center.x, center.y + size, center.z);
	axis[3] = quat_create(0, center.x, center.y, center.z + size);
	return (axis);
}