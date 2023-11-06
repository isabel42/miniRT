/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:18:29 by lsohler           #+#    #+#             */
/*   Updated: 2023/11/05 18:05:15 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quat	*init_axis(t_vec3d center, float size)
{
	t_quat	*axis;

	axis = malloc(sizeof(t_quat) * 4);
	if (!axis)
		ft_exit("Malloc");
	axis[0] = quat_create(0, center.x, center.y, center.z);
	axis[1] = quat_create(0, center.x + size, center.y, center.z);
	axis[2] = quat_create(0, center.x, center.y + size, center.z);
	axis[3] = quat_create(0, center.x, center.y, center.z + size);
	return (axis);
}

void	apply_cam_dir(t_scenario *scena, t_quat *c)
{
	int		i;
	t_vec3d	offset;

	i = 0;
	offset = scena->cam->pos;
	while (i <= 4)
	{
		c[i] = quat_sub_offset(c[i], offset);
		c[i] = quat_multiply(
				quat_multiply(scena->cam->dir,
					c[i]),
				quat_conjugate(scena->cam->dir));
		c[i] = quat_add_offset(c[i], offset);
		i++;
	}
}

t_quat	*init_quat_camera(t_scenario *scena, int dist)
{
	t_quat	*c;
	t_vec3d	pos;
	float	pl_h;
	float	pl_w;

	pos = scena->cam->pos;
	dist = (WIDTH / 2.0) / tan(ft_deg_to_rad(scena->cam->fov / 2.00));
	pl_w = WIDTH;
	pl_h = HEIGHT;
	c = malloc(sizeof(t_quat) * 5);
	if (!c)
		ft_exit("Malloc");
	c[0] = quat_create(0, pos.x - (pl_w / 2), pos.y + (pl_h / 2), pos.z + dist);
	c[1] = quat_create(0, pos.x + (pl_w / 2), pos.y + (pl_h / 2), pos.z + dist);
	c[2] = quat_create(0, pos.x + (pl_w / 2), pos.y - (pl_h / 2), pos.z + dist);
	c[3] = quat_create(0, pos.x - (pl_w / 2), pos.y - (pl_h / 2), pos.z + dist);
	c[4] = quat_create(0, pos.x, pos.y, pos.z);
	apply_cam_dir(scena, c);
	return (c);
}

t_quat	*init_quat_box(void)
{
	t_quat	*box;
	int		half_size;

	box = malloc(sizeof(t_quat) * 8);
	if (!box)
		ft_exit("Malloc");
	half_size = 300;
	box[0] = quat_create(0, -half_size, -half_size, -half_size);
	box[1] = quat_create(0, -half_size, -half_size, half_size);
	box[2] = quat_create(0, -half_size, half_size, half_size);
	box[3] = quat_create(0, -half_size, half_size, -half_size);
	box[4] = quat_create(0, half_size, -half_size, -half_size);
	box[5] = quat_create(0, half_size, -half_size, half_size);
	box[6] = quat_create(0, half_size, half_size, half_size);
	box[7] = quat_create(0, half_size, half_size, -half_size);
	return (box);
}
